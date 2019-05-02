// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SWidget.h"
#include "IPropertyTypeCustomization.h"
#include "Widgets/Input/SComboButton.h"
#include "Widgets/Views/STableViewBase.h"
#include "Widgets/Views/STableRow.h"
#include "Widgets/Views/SListView.h"
#include "PropertyCustomizationHelpers.h"
#include "IPropertyUtilities.h"

#define LOCTEXT_NAMESPACE "FResourceHandleCustomizationLayout"

struct FAssetData;

/**
 * Customizes a DataTable asset to use a dropdown
 */
class FResourceHandleCustomizationLayout : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance()
	{
		return MakeShareable(new FResourceHandleCustomizationLayout);
	}

	/** IPropertyTypeCustomization interface */
	void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

private:

	bool ShouldFilterAsset(const FAssetData& AssetData);

	/** Init the contents the combobox sources its data off */
	TSharedPtr<FString> InitWidgetContent();

	/** Returns the ListView for the ComboButton */
	TSharedRef<SWidget> GetListContent();

	/** Delegate to refresh the drop down when the datatable changes */
	void OnDataTableChanged();

	/** Return the representation of the the row names to display */
	TSharedRef<ITableRow> HandleRowNameComboBoxGenerateWidget(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable);

	/** Display the current selection */
	FText GetRowNameComboBoxContentText() const;

	/** Update the root data on a change of selection */
	void OnSelectionChanged(TSharedPtr<FString> SelectedItem, ESelectInfo::Type SelectInfo);

	/** Called by Slate when the filter box changes text. */
	void OnFilterTextChanged(const FText& InFilterText);

	void HandleMenuOpen();

	void OnSearchForReferences();

	/** The comboButton objects */
	TSharedPtr<SComboButton> RowNameComboButton;
	TSharedPtr<class SSearchBox> SearchBox;
	TSharedPtr<SListView<TSharedPtr<FString>>> RowNameComboListView;
	TSharedPtr<FString> CurrentSelectedItem;
	/** Handle to the struct properties being customized */
	TSharedPtr<IPropertyHandle> StructPropertyHandle;
	TSharedPtr<IPropertyHandle> DataTablePropertyHandle;
	TSharedPtr<IPropertyHandle> RowNamePropertyHandle;
	/** A cached copy of strings to populate the combo box */
	TArray<TSharedPtr<FString>> RowNames;
	/** The MetaData derived filter for the row type */
	FName RowTypeFilter;
};

#undef LOCTEXT_NAMESPACE
