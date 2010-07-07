#include "Precompile.h"
#include "Project.h"

#include "Foundation/Reflect/Serializers.h"

using namespace Luna;

REFLECT_DEFINE_CLASS( Project )

void Project::EnumerateClass( Reflect::Compositor< Project >& comp )
{
    comp.GetComposite().m_UIName = TXT( "Project" );
    Reflect::Field* fieldPaths = comp.AddField( &Project::m_Paths, "m_Paths", Reflect::FieldFlags::Path );
}

Project::Project()
{
}