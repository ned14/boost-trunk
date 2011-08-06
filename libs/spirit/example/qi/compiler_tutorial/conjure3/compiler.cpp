/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "config.hpp"
#include "compiler.hpp"
#include "annotation.hpp"
#include "vm.hpp"

#include <boost/foreach.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include <set>

namespace client { namespace code_gen
{
    value::value(
        llvm::Value* v,
        bool is_lvalue_,
        llvm::IRBuilder<>* builder)
      : v(v),
        is_lvalue_(is_lvalue_),
        builder(builder)
    {}

    value::value(value const& rhs)
      : v(rhs.v),
        is_lvalue_(rhs.is_lvalue_),
        builder(rhs.builder)
    {}

    value::value(unsigned int x)
      : v(llvm::ConstantInt::get(context(), llvm::APInt(int_size, x))),
        is_lvalue_(false),
        builder(0)
    {}

    value::value(int x)
      : v(llvm::ConstantInt::get(context(), llvm::APInt(int_size, x))),
        is_lvalue_(false),
        builder(0)
    {}

    value::value(bool x)
      : v(llvm::ConstantInt::get(context(), llvm::APInt(1, x))),
        is_lvalue_(false),
        builder(0)
    {}

    value::operator llvm::Value*() const
    {
        if (is_lvalue_)
        {
            BOOST_ASSERT(builder != 0);
            return builder->CreateLoad(v, v->getName());
        }
        return v;
    }

    value& value::operator=(value const& rhs)
    {
        v = rhs.v;
        is_lvalue_ = rhs.is_lvalue_;
        builder = rhs.builder;
        return *this;
    }

    value& value::assign(value const& rhs)
    {
        BOOST_ASSERT(is_lvalue());
        BOOST_ASSERT(builder != 0);
        builder->CreateStore(rhs, v);
        return *this;
    }

    namespace
    {
        //  Create an alloca instruction in the entry block of
        //  the function. This is used for mutable variables etc.
        llvm::AllocaInst*
        create_entry_block_alloca(
            llvm::Function* function,
            char const* name,
            llvm::LLVMContext& context)
        {
            llvm::IRBuilder<> builder(
                &function->getEntryBlock(),
                function->getEntryBlock().begin());

            return builder.CreateAlloca(
                llvm::Type::getIntNTy(context, int_size), 0, name);
        }
    }

    lvalue::lvalue(llvm::IRBuilder<>& builder, char const* name)
      : value(
            create_entry_block_alloca(
                builder.GetInsertBlock()->getParent(),
                name,
                context()),
        true, &builder)
    {
    }

    void compiler::init_fpm()
    {
        // Set up the optimizer pipeline.  Start with registering info about how the
        // target lays out data structures.
        fpm.add(new llvm::TargetData(*vm.execution_engine()->getTargetData()));
        // Provide basic AliasAnalysis support for GVN.
        fpm.add(llvm::createBasicAliasAnalysisPass());
        // Promote allocas to registers.
        fpm.add(llvm::createPromoteMemoryToRegisterPass());
        // Do simple "peephole" optimizations and bit-twiddling optzns.
        fpm.add(llvm::createInstructionCombiningPass());
        // Reassociate expressions.
        fpm.add(llvm::createReassociatePass());
        // Eliminate Common SubExpressions.
        fpm.add(llvm::createGVNPass());
        // Simplify the control flow graph (deleting unreachable blocks, etc).
        fpm.add(llvm::createCFGSimplificationPass());

        fpm.doInitialization();
    }

    value compiler::operator()(unsigned int x)
    {
        return value(x);
    }

    value compiler::operator()(bool x)
    {
        return value(x);
    }

    value compiler::operator()(ast::literal const& x)
    {
        return boost::apply_visitor(*this, x.get());
    }

    value compiler::operator()(ast::identifier const& x)
    {
        // Look this variable up in the function.
        lvalue value = named_values[x.name];
        if (!value)
        {
            error_handler(x.id, "Undeclared variable: " + x.name);
            return 0;
        }
        return value;
    }

    value compiler::operator()(ast::unary const& x)
    {
        value operand = boost::apply_visitor(*this, x.operand_);
        if (!operand)
            return 0;

        switch (x.operator_)
        {
            case token_ids::compl_:
                return builder.CreateXor(
                    operand, value(-1), "compl_tmp");
            case token_ids::minus:
                return builder.CreateNeg(operand, "neg_tmp");
            case token_ids::not_:
                return builder.CreateNot(operand, "not_tmp");
            case token_ids::plus:
                return operand;
            case token_ids::plus_plus:
            {
                value r = builder.CreateAdd(operand, value(1), "add_tmp");
                operand.assign(r);
                return operand;
            }
            case token_ids::minus_minus:
            {
                value r = builder.CreateSub(operand, value(1), "sub_tmp");
                operand.assign(r);
                return operand;
            }
            default: BOOST_ASSERT(0); return 0;
        }
    }

    value compiler::operator()(ast::function_call const& x)
    {
        llvm::Function* callee = vm.module()->getFunction(x.function_name.name);
        if (!callee)
        {
            error_handler(x.function_name.id, "Function not found: " + x.function_name.name);
            return false;
        }

        if (callee->arg_size() != x.args.size())
        {
            error_handler(x.function_name.id, "Wrong number of arguments: " + x.function_name.name);
            return 0;
        }

        std::vector<llvm::Value*> args;
        BOOST_FOREACH(ast::expression const& expr, x.args)
        {
            args.push_back((*this)(expr));
            if (args.back() == 0)
                return 0;
        }

        return builder.CreateCall(callee, args.begin(), args.end(), "calltmp");
    }

    namespace
    {
        int precedence[] = {
            // precedence 1
            1, // op_comma

            // precedence 2
            2, // op_assign
            2, // op_plus_assign
            2, // op_minus_assign
            2, // op_times_assign
            2, // op_divide_assign
            2, // op_mod_assign
            2, // op_bit_and_assign
            2, // op_bit_xor_assign
            2, // op_bitor_assign
            2, // op_shift_left_assign
            2, // op_shift_right_assign

            // precedence 3
            3, // op_logical_or

            // precedence 4
            4, // op_logical_and

            // precedence 5
            5, // op_bit_or

            // precedence 6
            6, // op_bit_xor

            // precedence 7
            7, // op_bit_and

            // precedence 8
            8, // op_equal
            8, // op_not_equal

            // precedence 9
            9, // op_less
            9, // op_less_equal
            9, // op_greater
            9, // op_greater_equal

            // precedence 10
            10, // op_shift_left
            10, // op_shift_right

            // precedence 11
            11, // op_plus
            11, // op_minus

            // precedence 12
            12, // op_times
            12, // op_divide
            12 // op_mod
        };
    }

    inline int precedence_of(token_ids::type op)
    {
        return precedence[op & 0xFF];
    }

    value compiler::compile_binary_expression(
        value lhs, value rhs, token_ids::type op)
    {
        switch (op)
        {
            case token_ids::plus: return builder.CreateAdd(lhs, rhs, "addtmp");
            case token_ids::minus: return builder.CreateSub(lhs, rhs, "subtmp");
            case token_ids::times: return builder.CreateMul(lhs, rhs, "multmp");
            case token_ids::divide: return builder.CreateSDiv(lhs, rhs, "divtmp");
            case token_ids::mod: return builder.CreateSRem(lhs, rhs, "modtmp");

            case token_ids::bit_or: return builder.CreateOr(lhs, rhs, "ortmp");
            case token_ids::bit_xor: return builder.CreateXor(lhs, rhs, "xortmp");
            case token_ids::bit_and: return builder.CreateAnd(lhs, rhs, "andtmp");
            case token_ids::shift_left: return builder.CreateShl(lhs, rhs, "shltmp");
            case token_ids::shift_right: return builder.CreateLShr(lhs, rhs, "shrtmp");

            case token_ids::equal: return builder.CreateICmpEQ(lhs, rhs, "eqtmp");
            case token_ids::not_equal: return builder.CreateICmpNE(lhs, rhs, "netmp");
            case token_ids::less: return builder.CreateICmpSLT(lhs, rhs, "slttmp");
            case token_ids::less_equal: return builder.CreateICmpSLE(lhs, rhs, "sletmp");
            case token_ids::greater: return builder.CreateICmpSGT(lhs, rhs, "sgttmp");
            case token_ids::greater_equal: return builder.CreateICmpSGE(lhs, rhs, "sgetmp");

            case token_ids::logical_or: return builder.CreateOr(lhs, rhs, "ortmp");
            case token_ids::logical_and: return builder.CreateAnd(lhs, rhs, "andtmp");
            default: BOOST_ASSERT(0); return 0;
        }
    }

    // The Shunting-yard algorithm
    value compiler::compile_expression(
        int min_precedence,
        value lhs,
        std::list<ast::operation>::const_iterator& rest_begin,
        std::list<ast::operation>::const_iterator rest_end)
    {
        while ((rest_begin != rest_end) &&
            (precedence_of(rest_begin->operator_) >= min_precedence))
        {
            token_ids::type op = rest_begin->operator_;
            value rhs = boost::apply_visitor(*this, rest_begin->operand_);
            if (!rhs)
                return 0;
            ++rest_begin;

            while ((rest_begin != rest_end) &&
                (precedence_of(rest_begin->operator_) > precedence_of(op)))
            {
                token_ids::type next_op = rest_begin->operator_;
                rhs = compile_expression(
                    precedence_of(next_op), rhs, rest_begin, rest_end);
            }

            lhs = compile_binary_expression(lhs, rhs, op);
        }
        return lhs;
    }

    value compiler::operator()(ast::expression const& x)
    {
        value lhs = boost::apply_visitor(*this, x.first);
        if (!lhs)
            return 0;
        std::list<ast::operation>::const_iterator rest_begin = x.rest.begin();
        return compile_expression(0, lhs, rest_begin, x.rest.end());
    }

    value compiler::operator()(ast::assignment const& x)
    {
        if (named_values.find(x.lhs.name) == named_values.end())
        {
            error_handler(x.lhs.id, "Undeclared variable: " + x.lhs.name);
            return 0;
        }

        lvalue lhs = named_values[x.lhs.name];
        value rhs = (*this)(x.rhs);
        if (!rhs)
            return 0;

        if (x.operator_ == token_ids::assign)
        {
            lhs.assign(rhs);
            return lhs;
        }

        value result;
        switch (x.operator_)
        {
            case token_ids::plus_assign:
                result = builder.CreateAdd(lhs, rhs, "addtmp");
                break;

            case token_ids::minus_assign:
                result = builder.CreateSub(lhs, rhs, "subtmp");
                break;

            case token_ids::times_assign:
                result = builder.CreateMul(lhs, rhs, "multmp");
                break;

            case token_ids::divide_assign:
                result = builder.CreateSDiv(lhs, rhs, "divtmp");
                break;

            case token_ids::mod_assign:
                result = builder.CreateSRem(lhs, rhs, "modtmp");
                break;

            case token_ids::bit_and_assign:
                result = builder.CreateAnd(lhs, rhs, "andtmp");
                break;

            case token_ids::bit_xor_assign:
                result = builder.CreateXor(lhs, rhs, "xortmp");
                break;

            case token_ids::bit_or_assign:
                result = builder.CreateOr(lhs, rhs, "ortmp");
                break;

            case token_ids::shift_left_assign:
                result = builder.CreateShl(lhs, rhs, "shltmp");
                break;

            case token_ids::shift_right_assign:
                result = builder.CreateLShr(lhs, rhs, "shrtmp");
                break;

            default: BOOST_ASSERT(0); return 0;
        }

        lhs.assign(result);
        return lhs;
    }

    bool compiler::operator()(ast::variable_declaration const& x)
    {
        if (named_values.find(x.lhs.name) != named_values.end())
        {
            error_handler(x.lhs.id, "Duplicate variable: " + x.lhs.name);
            return false;
        }

        value init;
        std::string const& var = x.lhs.name;

        if (x.rhs) // if there's an RHS initializer
        {
            init = (*this)(*x.rhs);
            if (!init) // don't add the variable if the RHS fails
                return false;
        }

        lvalue alloca(builder, var.c_str());
        if (init)
            alloca.assign(init);

        // Remember this binding.
        named_values[var] = alloca;
        return true;
    }

    struct compiler::statement_compiler : compiler
    {
        typedef bool result_type;
    };

    compiler::statement_compiler& compiler::as_statement()
    {
        return *static_cast<statement_compiler*>(this);
    }

    bool compiler::operator()(ast::statement const& x)
    {
        if (boost::get<ast::nil>(&x) != 0) // empty statement
            return true;
        return boost::apply_visitor(as_statement(), x);
    }

    bool compiler::operator()(ast::statement_list const& x)
    {
        BOOST_FOREACH(ast::statement const& s, x)
        {
            if (!(*this)(s))
                return false;
        }
        return true;
    }

    bool compiler::operator()(ast::if_statement const& x)
    {
        value condition = (*this)(x.condition);
        if (!condition)
            return 0;

        llvm::Function* function = builder.GetInsertBlock()->getParent();

        // Create blocks for the then and else cases.  Insert the 'then' block at the
        // end of the function.
        llvm::BasicBlock* then_block = llvm::BasicBlock::Create(context(), "if.then", function);
        llvm::BasicBlock* else_block = 0;
        llvm::BasicBlock* exit_block = 0;

        if (x.else_)
        {
            else_block = llvm::BasicBlock::Create(context(), "if.else");
            builder.CreateCondBr(condition, then_block, else_block);
        }
        else
        {
            exit_block = llvm::BasicBlock::Create(context(), "if.end");
            builder.CreateCondBr(condition, then_block, exit_block);
        }

        // Emit then value.
        builder.SetInsertPoint(then_block);
        if (!(*this)(x.then))
            return 0;
        if (then_block->getTerminator() == 0)
        {
            if (exit_block == 0)
                exit_block = llvm::BasicBlock::Create(context(), "if.end");
            builder.CreateBr(exit_block);
        }
        // Codegen of 'then' can change the current block, update then_block
        then_block = builder.GetInsertBlock();

        if (x.else_)
        {
            // Emit else block.
            function->getBasicBlockList().push_back(else_block);
            builder.SetInsertPoint(else_block);
            if (!(*this)(*x.else_))
                return 0;
            if (else_block->getTerminator() == 0)
            {
                if (exit_block == 0)
                    exit_block = llvm::BasicBlock::Create(context(), "if.end");
                builder.CreateBr(exit_block);
            }
            // Codegen of 'else' can change the current block, update else_block
            else_block = builder.GetInsertBlock();
        }

        if (exit_block != 0)
        {
            // Emit exit block
            function->getBasicBlockList().push_back(exit_block);
            builder.SetInsertPoint(exit_block);
        }
        return true;
    }

    bool compiler::operator()(ast::while_statement const& x)
    {
        llvm::Function* function = builder.GetInsertBlock()->getParent();

        llvm::BasicBlock* cond_block = llvm::BasicBlock::Create(context(), "while.cond", function);
        llvm::BasicBlock* body_block = llvm::BasicBlock::Create(context(), "while.body");
        llvm::BasicBlock* exit_block = llvm::BasicBlock::Create(context(), "while.end");

        builder.CreateBr(cond_block);
        builder.SetInsertPoint(cond_block);
        value condition = (*this)(x.condition);
        if (!condition)
            return false;
        builder.CreateCondBr(condition, body_block, exit_block);
        function->getBasicBlockList().push_back(body_block);
        builder.SetInsertPoint(body_block);

        if (!(*this)(x.body))
            return false;

        if (body_block->getTerminator() == 0)
            builder.CreateBr(cond_block); // loop back

        // Emit exit block
        function->getBasicBlockList().push_back(exit_block);
        builder.SetInsertPoint(exit_block);

        return true;
    }

    bool compiler::operator()(ast::return_statement const& x)
    {
        if (void_return)
        {
            if (x.expr)
            {
                error_handler(
                    x.id, "'void' function returning a value: ");
                return false;
            }
        }
        else
        {
            if (!x.expr)
            {
                error_handler(
                    x.id, current_function_name
                    + " function must return a value: ");
                return false;
            }
        }

        if (x.expr)
        {
            value return_val = (*this)(*x.expr);
            if (!return_val)
                return false;
            return_alloca.assign(return_val);
        }

        builder.CreateBr(return_block);
        return true;
    }

    llvm::Function* compiler::function_decl(ast::function const& x)
    {
        void_return = x.return_type == "void";
        current_function_name = x.function_name.name;

        llvm::Type* int_type =
            llvm::Type::getIntNTy(context(), int_size);
        llvm::Type* void_type = llvm::Type::getVoidTy(context());

        std::vector<llvm::Type*> ints(x.args.size(), int_type);
        llvm::Type* return_type = void_return ? void_type : int_type;

        llvm::FunctionType* function_type =
            llvm::FunctionType::get(void_return ? void_type : int_type, ints, false);

        llvm::Function* function =
            llvm::Function::Create(
                function_type, llvm::Function::ExternalLinkage,
                current_function_name, vm.module());

        // If function conflicted, the function already exixts. If it has a
        // body, don't allow redefinition or reextern.
        if (function->getName() != current_function_name)
        {
            // Delete the one we just made and get the existing one.
            function->eraseFromParent();
            function = vm.module()->getFunction(current_function_name);

            // If function already has a body, reject this.
            if (!function->empty())
            {
                error_handler(
                    x.function_name.id,
                    "Duplicate function: " + x.function_name.name);
                return 0;
            }

            // If function took a different number of args, reject.
            if (function->arg_size() != x.args.size())
            {
                error_handler(
                    x.function_name.id,
                    "Redefinition of function with different # args: "
                        + x.function_name.name);
                return 0;
            }

            // Set names for all arguments.
            llvm::Function::arg_iterator iter = function->arg_begin();
            BOOST_FOREACH(ast::identifier const& arg, x.args)
            {
                iter->setName(arg.name);
                ++iter;
            }
        }
        return function;
    }

    void compiler::function_allocas(ast::function const& x, llvm::Function* function)
    {
        // CreateArgumentAllocas - Create an alloca for each argument and register the
        // argument in the symbol table so that references to it will succeed.
        llvm::Function::arg_iterator iter = function->arg_begin();
        BOOST_FOREACH(ast::identifier const& arg, x.args)
        {
            // Create an alloca for this variable.
            lvalue alloca(builder, arg.name.c_str());

            // Store the initial value into the alloca.
            alloca.assign(value(iter));

            // Add arguments to variable symbol table.
            named_values[arg.name] = alloca;
            ++iter;
        }

        if (!void_return)
        {
            // Create an alloca for the return value
            return_alloca = lvalue(builder, "return.val");
        }
    }

    bool compiler::operator()(ast::function const& x)
    {
        ///////////////////////////////////////////////////////////////////////
        // the signature:
        llvm::Function* function = function_decl(x);
        if (function == 0)
            return false;

        ///////////////////////////////////////////////////////////////////////
        // the body:
        if (x.body) // compile the body if this is not a prototype
        {
            // Create a new basic block to start insertion into.
            llvm::BasicBlock* block =
                llvm::BasicBlock::Create(context(), "entry", function);
            builder.SetInsertPoint(block);

            function_allocas(x, function);
            return_block = llvm::BasicBlock::Create(context(), "return");

            if (!(*this)(*x.body))
            {
                // Error reading body, remove function.
                function->eraseFromParent();
                return false;
            }

            llvm::BasicBlock* last_block =
                &function->getBasicBlockList().back();

            // If the last block is unterminated, connect it to return_block
            if (last_block->getTerminator() == 0)
            {
                builder.SetInsertPoint(last_block);
                builder.CreateBr(return_block);
            }

            function->getBasicBlockList().push_back(return_block);
            builder.SetInsertPoint(return_block);

            if (void_return)
                builder.CreateRetVoid();
            else
                builder.CreateRet(return_alloca);

            //~ vm.module()->dump();

            // Validate the generated code, checking for consistency.
            llvm::verifyFunction(*function);

            // Optimize the function.
            fpm.run(*function);
        }

        return true;
    }

    bool compiler::operator()(ast::function_list const& x)
    {
        BOOST_FOREACH(ast::function const& f, x)
        {
            named_values.clear(); // clear the variables
            if (!(*this)(f))
                return false;
        }
        return true;
    }
}}

