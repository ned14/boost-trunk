import os.path

#==============================================================================
# Exporter
#==============================================================================
class Exporter:
    'Base class for objects capable to generate boost.python code.'

    INDENT = ' ' * 4
    
    def __init__(self, info, parser_tail=None):
        self.info = info
        self.parser_tail = parser_tail
    

    def Name(self):
        return self.info.name


    def Tail(self):
        return self.parser_tail

        
    def Parse(self, parser):
        self.parser = parser
        header = self.info.include
        tail = self.parser_tail
        declarations, parser_header = parser.parse(header, tail)
        self.parser_header = parser_header
        self.SetDeclarations(declarations)


    def SetParsedHeader(self, parsed_header):
        self.parser_header = parsed_header 


    def SetDeclarations(self, declarations):
        self.declarations = declarations

        
    def GenerateCode(self, codeunit, exported_names):
        self.WriteInclude(codeunit)
        self.Export(codeunit, exported_names)        


    def WriteInclude(self, codeunit):
        codeunit.Write('include', '#include <%s>\n' % self.info.include)
        
        
    def Export(self, codeunit, exported_names):
        'subclasses must override this to do the real work'
        pass
    
                    
    def GetDeclarations(self, fullname):
        decls = []
        for decl in self.declarations:
            if decl.FullName() == fullname:
                decls.append(decl)
        if not decls:
            raise RuntimeError, 'no %s declaration found!' % fullname
        return decls


    def GetDeclaration(self, fullname):
        decls = self.GetDeclarations(fullname)
        assert len(decls) == 1
        return decls[0]


    def Order(self):
        '''Returns a string that uniquely identifies this instance. All
        exporters will be sorted by Order before being exported.
        '''
        raise NotImplementedError


    def Unit(self):
        return self.info.include


    def Header(self):
        return self.info.include
