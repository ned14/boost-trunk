from boost.build.build import action

action.action ('Clean', 'rm -rf "$(>)"')

action.action ('MkDir', 'mkdir -p "$(<)"')
