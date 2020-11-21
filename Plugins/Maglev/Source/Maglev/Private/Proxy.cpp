#ifdef WITH_EDITOR
#include "Maglev.h"

FPrimitiveSceneProxy* UMaglev::CreateSceneProxy() {
	{
		/** Represents a UBoxComponent to the scene manager. */
		class FMaglevSceneProxy : public FPrimitiveSceneProxy
		{
		public:
			FMaglevSceneProxy(UMaglev* InComponent)
				: FPrimitiveSceneProxy(InComponent)
			{
				bWillEverBeLit = false;
				Maglev = InComponent; 
			}

			virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override
			{
				QUICK_SCOPE_CYCLE_COUNTER(STAT_MaglevSceneProxy_GetDynamicMeshElements);

				const FMatrix& Transform = GetLocalToWorld();

				for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
				{
					if (VisibilityMap && (1 << ViewIndex))
					{
						const FSceneView* View = Views[ViewIndex];
						const FLinearColor DrawColor = GetViewSelectionColor(FColor::Green, *View, IsSelected(), IsHovered(), true, IsIndividuallySelected());

						FPrimitiveDrawInterface* PDI = Collector.GetPDI(ViewIndex);

						float Distance = Maglev->Distance;
						FVector Location = Transform.GetOrigin() + (Transform.GetUnitAxis(EAxis::X)*Distance*0.5);
						DrawWireCapsule(PDI, Location, Transform.GetUnitAxis(EAxis::Z), Transform.GetUnitAxis(EAxis::Y), Transform.GetUnitAxis(EAxis::X), DrawColor, Maglev->Radius, Distance*0.5+Maglev->Radius, 16, SDPG_World);
					}
				}
			}

			virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override
			{
				const bool bProxyVisible = IsSelected();

				FPrimitiveViewRelevance Result;
				Result.bDrawRelevance = (IsShown(View));
				Result.bDynamicRelevance = true;
				Result.bShadowRelevance = false;
				Result.bEditorPrimitiveRelevance = UseEditorCompositing(View);
				return Result;
			}
			virtual uint32 GetMemoryFootprint(void) const override { return(sizeof(*this) + GetAllocatedSize()); }
			uint32 GetAllocatedSize(void) const { return(FPrimitiveSceneProxy::GetAllocatedSize()); }
			virtual SIZE_T GetTypeHash() const override { return 0; }

		private:
			UMaglev* Maglev;
		};

		return new FMaglevSceneProxy(this);
	}
};

#endif