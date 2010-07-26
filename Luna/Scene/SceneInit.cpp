#include "Precompile.h"
#include "SceneInit.h"

// Libraries
#include "Foundation/InitializerStack.h"
#include "Foundation/Reflect/Registry.h"
#include "Application/RCS/Providers/Perforce/Perforce.h"
#include "Pipeline/Content/ContentInit.h"
#include "Pipeline/Content/ContentVersion.h"
#include "Pipeline/Asset/AssetInit.h"

// Types
#include "SceneDocument.h"
#include "ScenePreferences.h"

#include "Tool.h"
#include "CreateTool.h"
#include "DuplicateTool.h"

#include "ScaleManipulator.h"
#include "RotateManipulator.h"
#include "TranslateManipulator.h"

#include "HierarchyNodeType.h"
#include "JointTransform.h"
#include "PivotTransform.h"

#include "Layer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Skin.h"

#include "Curve.h"
#include "Point.h"
#include "CurveCreateTool.h"
#include "CurveEditTool.h"

#include "Instance.h"
#include "InstanceType.h"

#include "Entity.h"
#include "EntityAssetSet.h"
#include "EntityType.h"
#include "EntityCreateTool.h"

#include "Locator.h"
#include "LocatorType.h"
#include "LocatorCreateTool.h"

#include "Volume.h"
#include "VolumeType.h"
#include "VolumeCreateTool.h"

#include "NavMesh.h"
#include "NavMeshCreateTool.h"

#include "Light.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "AmbientLight.h"

#include "ScenePreferences.h"
#include "ViewportPreferences.h"
#include "GridPreferences.h"
#include "Preferences.h"

using namespace Luna;

static i32 g_InitCount = 0;
static Nocturnal::InitializerStack g_InitializerStack;

void Luna::SceneInitialize()
{
  if ( ++g_InitCount == 1 )
  {
    // core library initiailization
    g_InitializerStack.Push( Perforce::Initialize, Perforce::Cleanup );
    g_InitializerStack.Push( Reflect::Initialize, Reflect::Cleanup );
    g_InitializerStack.Push( Content::Initialize, Content::Cleanup );
    g_InitializerStack.Push( Asset::Initialize, Asset::Cleanup );

    // reflect types defined in this library (after Reflect::Initialize above)
    g_InitializerStack.Push( Reflect::RegisterEnumeration<CameraModes::CameraMode>( &CameraModes::CameraModeEnumerateEnumeration, TXT( "CameraMode" ) ) ); 
    g_InitializerStack.Push( Reflect::RegisterEnumeration<GeometryModes::GeometryMode>( &GeometryModes::GeometryModeEnumerateEnumeration, TXT( "GeometryMode" ) ) ); 
    g_InitializerStack.Push( Reflect::RegisterEnumeration<ViewColorModes::ViewColorMode>( &ViewColorModes::ViewColorModeEnumerateEnumeration, TXT( "ViewColorMode" ) ) ); 
    g_InitializerStack.Push( Reflect::RegisterEnumeration<GridUnits::GridUnit>( &GridUnits::GridUnitEnumerateEnumeration, TXT( "GridUnit" ) ) ); 
    g_InitializerStack.Push( Reflect::RegisterEnumeration<ManipulatorSpaces::ManipulatorSpace>( &ManipulatorSpaces::ManipulatorSpaceEnumerateEnumeration, TXT( "ManipulatorSpace" ) ) ); 
    g_InitializerStack.Push( Reflect::RegisterEnumeration<TranslateSnappingModes::TranslateSnappingMode>( &TranslateSnappingModes::TranslateSnappingModeEnumerateEnumeration, TXT( "TranslateSnappingMode" ) ) ); 
    g_InitializerStack.Push( Reflect::RegisterEnumeration<ShadingMode>( &ShadingModes::EnumerateEnumeration, TXT( "ShadingMode" ) ) );

    // luna types 
    g_InitializerStack.Push( SceneDocument::InitializeType, SceneDocument::CleanupType );

    g_InitializerStack.Push( Tool::InitializeType, Tool::CleanupType );
    g_InitializerStack.Push( CreateTool::InitializeType, CreateTool::CleanupType );
    g_InitializerStack.Push( DuplicateTool::InitializeType, DuplicateTool::CleanupType );

    g_InitializerStack.Push( TransformManipulator::InitializeType, TransformManipulator::CleanupType );
    g_InitializerStack.Push( TranslateManipulator::InitializeType, TranslateManipulator::CleanupType );
    g_InitializerStack.Push( RotateManipulator::InitializeType, RotateManipulator::CleanupType );
    g_InitializerStack.Push( ScaleManipulator::InitializeType, ScaleManipulator::CleanupType );

    g_InitializerStack.Push( SceneGraph::InitializeType, SceneGraph::CleanupType );
    g_InitializerStack.Push( SceneNode::InitializeType, SceneNode::CleanupType );
    g_InitializerStack.Push( SceneNodeType::InitializeType, SceneNodeType::CleanupType );

    g_InitializerStack.Push( HierarchyNode::InitializeType, HierarchyNode::CleanupType );
    g_InitializerStack.Push( HierarchyNodeType::InitializeType, HierarchyNodeType::CleanupType );

    g_InitializerStack.Push( Transform::InitializeType, Transform::CleanupType );
    g_InitializerStack.Push( JointTransform::InitializeType, JointTransform::CleanupType );
    g_InitializerStack.Push( PivotTransform::InitializeType, PivotTransform::CleanupType );

    g_InitializerStack.Push( Layer::InitializeType, Layer::CleanupType );
    g_InitializerStack.Push( Shader::InitializeType, Shader::CleanupType );
    g_InitializerStack.Push( Mesh::InitializeType, Mesh::CleanupType );
    g_InitializerStack.Push( Skin::InitializeType, Skin::CleanupType );

    g_InitializerStack.Push( Point::InitializeType, Point::CleanupType );
    g_InitializerStack.Push( Curve::InitializeType, Curve::CleanupType );
    g_InitializerStack.Push( CurveCreateTool::InitializeType, CurveCreateTool::CleanupType );
    g_InitializerStack.Push( CurveEditTool::InitializeType, CurveEditTool::CleanupType );

    g_InitializerStack.Push( Instance::InitializeType, Instance::CleanupType );
    g_InitializerStack.Push( InstanceSet::InitializeType, InstanceSet::CleanupType );
    g_InitializerStack.Push( InstanceType::InitializeType, InstanceType::CleanupType );

    g_InitializerStack.Push( Volume::InitializeType, Volume::CleanupType );
    g_InitializerStack.Push( VolumeType::InitializeType, VolumeType::CleanupType );
    g_InitializerStack.Push( VolumeCreateTool::InitializeType, VolumeCreateTool::CleanupType );

    g_InitializerStack.Push( Locator::InitializeType, Locator::CleanupType );
    g_InitializerStack.Push( LocatorType::InitializeType, LocatorType::CleanupType );
    g_InitializerStack.Push( LocatorCreateTool::InitializeType, LocatorCreateTool::CleanupType );

    g_InitializerStack.Push( Entity::InitializeType, Entity::CleanupType );
    g_InitializerStack.Push( EntityAssetSet::InitializeType, EntityAssetSet::CleanupType );
    g_InitializerStack.Push( EntityType::InitializeType, EntityType::CleanupType );
    g_InitializerStack.Push( EntityCreateTool::InitializeType, EntityCreateTool::CleanupType );

    g_InitializerStack.Push( Light::InitializeType, Light::CleanupType );
    g_InitializerStack.Push( SpotLight::InitializeType, SpotLight::CleanupType );
    g_InitializerStack.Push( PointLight::InitializeType, PointLight::CleanupType );
    g_InitializerStack.Push( DirectionalLight::InitializeType, DirectionalLight::CleanupType );
    g_InitializerStack.Push( AmbientLight::InitializeType, AmbientLight::CleanupType );

    g_InitializerStack.Push( Viewport::InitializeType, Viewport::CleanupType );
    g_InitializerStack.Push( Primitive::InitializeType, Primitive::CleanupType );

    g_InitializerStack.Push( NavMesh::InitializeType, NavMesh::CleanupType );
    g_InitializerStack.Push( NavMeshCreateTool::InitializeType, NavMeshCreateTool::CleanupType );
  }
}

void Luna::SceneCleanup()
{
  if ( --g_InitCount == 0 )
  {
    g_InitializerStack.Cleanup();
  }
}
