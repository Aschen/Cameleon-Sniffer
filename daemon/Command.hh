#ifndef COMMAND
# define COMMAND

# include <QString>

# include "modules/AModule.hh"

typedef struct  s_created_module
{
    AModule*    module;
    QString     usage;
}               CreatedModule;

typedef struct  s_start_module_args
{
    QString     type;
    QString     name;
    QStringList options;
}               StartModuleArgs;

#endif // COMMAND

