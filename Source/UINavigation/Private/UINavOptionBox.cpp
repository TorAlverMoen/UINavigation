// Copyright (C) 2019 Gonçalo Marques - All Rights Reserved

#include "UINavOptionBox.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UINavMacros.h"

void UUINavOptionBox::NativeConstruct()
{
	Super::BaseConstruct();

	PRAGMA_DISABLE_DEPRECATION_WARNINGS
	LeftButton->IsFocusable = false;
	RightButton->IsFocusable = false;
	PRAGMA_ENABLE_DEPRECATION_WARNINGS

	if (!LeftButton->OnClicked.IsBound())
		LeftButton->OnClicked.AddDynamic(this, &UUINavHorizontalComponent::NavigateLeft);
	
	if (!RightButton->OnClicked.IsBound())
		RightButton->OnClicked.AddDynamic(this, &UUINavHorizontalComponent::NavigateRight);
}

int UUINavOptionBox::GetMaxOptionIndex() const
{
	if (bUseNumberRange)
	{
		return (MaxRange - MinRange) / Interval;
	}
	else
	{
		return StringOptions.Num() - 1;
	}
}

void UUINavOptionBox::Update()
{
	Super::Update();

	NavText->SetText(bUseNumberRange ? 
		FText::FromString(FString::FromInt(MinRange + OptionIndex*Interval)) : 
		StringOptions.IsValidIndex(OptionIndex) ? StringOptions[OptionIndex] : FText());
}

