#pragma once

#include "Reflect/MetaStruct.h"
#include "Math/Point.h"
#include "Engine/Asset.h"
#include "Framework/ComponentDefinition.h"
#include "Foundation/DynamicArray.h"
#include "Framework/TaskScheduler.h"
#include "Framework/Entity.h"

#include "Graphics/Texture2d.h"
#include "Graphics/BufferedDrawer.h"
#include "Graphics/GraphicsManagerComponent.h"

namespace GameLibrary
{
	struct ScreenSpaceTextComponentDefinition;
	
	typedef Helium::StrongPtr<ScreenSpaceTextComponentDefinition> ScreenSpaceTextComponentDefinitionPtr;	
	typedef Helium::StrongPtr<const ScreenSpaceTextComponentDefinition> ConstScreenSpaceTextComponentDefinition;
	
	//////////////////////////////////////////////////////////////////////////
	// ScreenSpaceTextComponent
	class GAME_LIBRARY_API ScreenSpaceTextComponent : public Helium::Component
	{
	public:
		HELIUM_DECLARE_COMPONENT( GameLibrary::ScreenSpaceTextComponent, Helium::Component );
		static void PopulateMetaType( Helium::Reflect::MetaStruct& comp );

		ScreenSpaceTextComponent();
		
		void Initialize( const ScreenSpaceTextComponentDefinition &definition);

		void Render( Helium::GraphicsManagerComponent &rGraphicsManager );
		
	private:
		ConstScreenSpaceTextComponentDefinition m_Definition;
	};
	
	struct GAME_LIBRARY_API ScreenSpaceTextComponentDefinition : public Helium::ComponentDefinitionHelper<ScreenSpaceTextComponent, ScreenSpaceTextComponentDefinition>
	{
		HELIUM_DECLARE_CLASS( GameLibrary::ScreenSpaceTextComponentDefinition, Helium::ComponentDefinition );
		static void PopulateMetaType( Helium::Reflect::MetaStruct& comp );

		ScreenSpaceTextComponentDefinition();
	
		Helium::String m_Text;
		Helium::Simd::Vector2 m_Position;
	};

	struct GAME_LIBRARY_API DrawScreenSpaceTextTask : public Helium::TaskDefinition
	{
		HELIUM_DECLARE_TASK(DrawScreenSpaceTextTask)

		virtual void DefineContract(Helium::TaskContract &rContract);
	};
}
