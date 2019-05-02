// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ResourceHandleCustomization.h"
#include "DataTableEditor/Public/DataTableRowUtlis.h"
#include "Editor.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Widgets/Input/SSearchBox.h"
#include "IDetailChildrenBuilder.h"
#include "Engine/DataTable.h"
#include "Widgets/Text/STextBlock.h"
#include "Layout/Margin.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

#define LOCTEXT_NAMESPACE "FResourceHandleCustomizationLayout"

TSharedPtr<FString> FResourceHandleCustomizationLayout::InitWidgetContent()
{
	TSharedPtr<FString> InitialValue = MakeShareable(new FString(LOCTEXT("DataTable_None", "None").ToString()));

	FName RowName;
	const FPropertyAccess::Result RowResult = RowNamePropertyHandle->GetValue(RowName);
	RowNames.Empty();

	/** Get the properties we wish to work with */
	const UDataTable* DataTable = nullptr;
	DataTablePropertyHandle->GetValue((UObject * &)DataTable);

	if (DataTable != nullptr)
	{
		/** Extract all the row names from the RowMap */
		for (TMap<FName, uint8*>::TConstIterator Iterator(DataTable->GetRowMap()); Iterator; ++Iterator)
		{
			/** Create a simple array of the row names */
			TSharedRef<FString> RowNameItem = MakeShareable(new FString(Iterator.Key().ToString()));
			RowNames.Add(RowNameItem);

			/** Set the initial value to the currently selected item */
			if (Iterator.Key() == RowName)
			{
				InitialValue = RowNameItem;
			}
		}
	}

	/** Reset the initial value to ensure a valid entry is set */
	if (RowResult != FPropertyAccess::MultipleValues)
	{
		FName NewValue = FName(**InitialValue);
		RowNamePropertyHandle->SetValue(NewValue);
	}

	return InitialValue;
}

void FResourceHandleCustomizationLayout::CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	this->StructPropertyHandle = InStructPropertyHandle;

	if (StructPropertyHandle->HasMetaData(TEXT("RowType")))
	{
		const FString& RowType = StructPropertyHandle->GetMetaData(TEXT("RowType"));
		RowTypeFilter = FName(*RowType);
	}

	FSimpleDelegate OnDataTableChangedDelegate = FSimpleDelegate::CreateSP(this, &FResourceHandleCustomizationLayout::OnDataTableChanged);
	StructPropertyHandle->SetOnPropertyValueChanged(OnDataTableChangedDelegate);

	HeaderRow
	.NameContent()
	[
		InStructPropertyHandle->CreatePropertyNameWidget(FText::GetEmpty(), FText::GetEmpty(), false)
	];

	FDataTableRowUtils::AddSearchForReferencesContextMenu(HeaderRow, FExecuteAction::CreateSP(this, &FResourceHandleCustomizationLayout::OnSearchForReferences));
}

void FResourceHandleCustomizationLayout::CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	/** Get all the existing property handles */
	DataTablePropertyHandle = InStructPropertyHandle->GetChildHandle("DataTable");
	RowNamePropertyHandle = InStructPropertyHandle->GetChildHandle("RowName");

	if (DataTablePropertyHandle->IsValidHandle() && RowNamePropertyHandle->IsValidHandle())
	{
		/** Queue up a refresh of the selected item, not safe to do from here */
		StructCustomizationUtils.GetPropertyUtilities()->EnqueueDeferredAction(FSimpleDelegate::CreateSP(this, &FResourceHandleCustomizationLayout::OnDataTableChanged));

		/** Setup Change callback */
		FSimpleDelegate OnDataTableChangedDelegate = FSimpleDelegate::CreateSP(this, &FResourceHandleCustomizationLayout::OnDataTableChanged);
		DataTablePropertyHandle->SetOnPropertyValueChanged(OnDataTableChangedDelegate);

		/** Construct a asset picker widget with a custom filter */
		StructBuilder.AddCustomRow(LOCTEXT("DataTable_TableName", "Data Table"))
					.NameContent()
		[
			SNew(STextBlock)
				.Text(LOCTEXT("DataTable_TableName", "Data Table"))
			.Font(StructCustomizationUtils.GetRegularFont())
		]
		.ValueContent()
		.MaxDesiredWidth(0.0f) // don't constrain the combo button width
		[
			SNew(SObjectPropertyEntryBox)
				.PropertyHandle(DataTablePropertyHandle)
			.AllowedClass(UDataTable::StaticClass())
			.OnShouldFilterAsset(this, &FResourceHandleCustomizationLayout::ShouldFilterAsset)
		];

		/** Construct a combo box widget to select from a list of valid options */
		StructBuilder.AddCustomRow(LOCTEXT("DataTable_RowName", "Row Name"))
					.NameContent()
		[
			SNew(STextBlock)
				.Text(LOCTEXT("DataTable_RowName", "Row Name"))
			.Font(StructCustomizationUtils.GetRegularFont())
		]
		.ValueContent()
		.MaxDesiredWidth(0.0f) // don't constrain the combo button width
		[
			SAssignNew(RowNameComboButton, SComboButton)
				.ToolTipText(this, &FResourceHandleCustomizationLayout::GetRowNameComboBoxContentText)
			.OnGetMenuContent(this, &FResourceHandleCustomizationLayout::GetListContent)
			.OnComboBoxOpened(this, &FResourceHandleCustomizationLayout::HandleMenuOpen)
			.ContentPadding(FMargin(2.0f, 2.0f))
			.ButtonContent()
			[
				SNew(STextBlock)
				.Text(this, &FResourceHandleCustomizationLayout::GetRowNameComboBoxContentText)
			]
		];
	}
}

void FResourceHandleCustomizationLayout::HandleMenuOpen()
{
	FSlateApplication::Get().SetKeyboardFocus(SearchBox);
}

void FResourceHandleCustomizationLayout::OnSearchForReferences()
{
	if (CurrentSelectedItem.IsValid() && !CurrentSelectedItem->IsEmpty() && DataTablePropertyHandle.IsValid() && DataTablePropertyHandle->IsValidHandle())
	{
		UObject* SourceDataTable;
		DataTablePropertyHandle->GetValue(SourceDataTable);
		FName RowName(**CurrentSelectedItem);

		TArray<FAssetIdentifier> AssetIdentifiers;
		AssetIdentifiers.Add(FAssetIdentifier(SourceDataTable, RowName));

		FEditorDelegates::OnOpenReferenceViewer.Broadcast(AssetIdentifiers);
	}
}

TSharedRef<SWidget> FResourceHandleCustomizationLayout::GetListContent()
{
	SAssignNew(RowNameComboListView, SListView<TSharedPtr<FString> >)
		.ListItemsSource(&RowNames)
		.OnSelectionChanged(this, &FResourceHandleCustomizationLayout::OnSelectionChanged)
		.OnGenerateRow(this, &FResourceHandleCustomizationLayout::HandleRowNameComboBoxGenerateWidget)
		.SelectionMode(ESelectionMode::Single);

	// Ensure no filter is applied at the time the menu opens
	OnFilterTextChanged(FText::GetEmpty());

	if (CurrentSelectedItem.IsValid())
	{
		RowNameComboListView->SetSelection(CurrentSelectedItem);
	}

	return SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SAssignNew(SearchBox, SSearchBox)
				.OnTextChanged(this, &FResourceHandleCustomizationLayout::OnFilterTextChanged)
			]

			+ SVerticalBox::Slot()
			.FillHeight(1.f)
			[
				SNew(SBox)
				.MaxDesiredHeight(600)
				[
					RowNameComboListView.ToSharedRef()
				]
			];
}

void FResourceHandleCustomizationLayout::OnDataTableChanged()
{
	CurrentSelectedItem = InitWidgetContent();
	if (RowNameComboListView.IsValid())
	{
		RowNameComboListView->SetSelection(CurrentSelectedItem);
		RowNameComboListView->RequestListRefresh();
	}
}

TSharedRef<ITableRow> FResourceHandleCustomizationLayout::HandleRowNameComboBoxGenerateWidget(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	return
	SNew(STableRow<TSharedPtr<FString>>, OwnerTable)
	[
		SNew(STextBlock).Text(FText::FromString(*InItem))
	];
}

FText FResourceHandleCustomizationLayout::GetRowNameComboBoxContentText() const
{
	FString RowNameValue;
	const FPropertyAccess::Result RowResult = RowNamePropertyHandle->GetValue(RowNameValue);
	if (RowResult == FPropertyAccess::Success)
	{
		return FText::FromString(*RowNameValue);
	}
	if (RowResult == FPropertyAccess::Fail)
	{
		return LOCTEXT("DataTable_None", "None");
	}
	return LOCTEXT("MultipleValues", "Multiple Values");
}

void FResourceHandleCustomizationLayout::OnSelectionChanged(TSharedPtr<FString> SelectedItem, ESelectInfo::Type SelectInfo)
{
	if (SelectedItem.IsValid())
	{
		CurrentSelectedItem = SelectedItem;
		FName NewValue = FName(**SelectedItem);
		RowNamePropertyHandle->SetValue(NewValue);

		// Close the combo
		RowNameComboButton->SetIsOpen(false);
	}
}

void FResourceHandleCustomizationLayout::OnFilterTextChanged(const FText& InFilterText)
{
	FString CurrentFilterText = InFilterText.ToString();

	FName RowName;
	const FPropertyAccess::Result RowResult = RowNamePropertyHandle->GetValue(RowName);
	RowNames.Empty();

	/** Get the properties we wish to work with */
	const UDataTable* DataTable = nullptr;
	DataTablePropertyHandle->GetValue((UObject * &)DataTable);

	TArray<FString> AllRowNames;
	if (DataTable != nullptr)
	{
		for (TMap<FName, uint8*>::TConstIterator Iterator(DataTable->GetRowMap()); Iterator; ++Iterator)
		{
			FString RowString = Iterator.Key().ToString();
			AllRowNames.Add(RowString);
		}

		// Sort the names alphabetically.
		AllRowNames.Sort();
	}

	for (const FString& RowString : AllRowNames)
	{
		if (CurrentFilterText == TEXT("") || RowString.Contains(CurrentFilterText))
		{
			TSharedRef<FString> RowNameItem = MakeShareable(new FString(RowString));
			RowNames.Add(RowNameItem);
		}
	}

	RowNameComboListView->RequestListRefresh();
}

bool FResourceHandleCustomizationLayout::ShouldFilterAsset(const struct FAssetData& AssetData)
{
	if (!RowTypeFilter.IsNone())
	{
		const UDataTable* DataTable = Cast<UDataTable>(AssetData.GetAsset());
		if (DataTable->RowStruct && DataTable->RowStruct->GetFName() == RowTypeFilter)
		{
			return false;
		}
		return true;
	}
	return false;
}

#undef LOCTEXT_NAMESPACE
