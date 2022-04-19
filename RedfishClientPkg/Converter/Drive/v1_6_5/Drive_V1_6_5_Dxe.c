/** @file 
  The implementation of EFI Redfish JSON Structure DXE driver for below
  Redfish schema.
   - Drive.v1_6_5 

  (C) Copyright 2019-2021 Hewlett Packard Enterprise Development LP<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

  Auto-generated file by Redfish Schema C Structure Generator.
  https://github.com/DMTF/Redfish-Schema-C-Struct-Generator
  
  Copyright Notice:
  Copyright 2019-2021 Distributed Management Task Force, Inc. All rights reserved.
  License: BSD 3-Clause License. For full text see link: https://github.com/DMTF/Redfish-JSON-C-Struct-Converter/blob/master/LICENSE.md d

**/
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>

#include <Protocol/RestJsonStructure.h>

#include <jansson.h>
//
// EFI Redfish Resource Type Identifier.
//
#include <RedfishJsonStructure/Drive/v1_6_5/EfiDriveV1_6_5.h>
CHAR8 mResourceTypeStr [] = "#Drive";
BOOLEAN IsRevisonController = TRUE;

// Support Drive V1_6_5 
EFI_REST_JSON_STRUCTURE_SUPPORTED ResourceInterP [] = {
  {
    {
      (LIST_ENTRY *)&ResourceInterP[0], (LIST_ENTRY *)&ResourceInterP[0]
    },
    {
      {
        "Drive",
        "1",
        "6",
        "5"
      },
      "Drive"
    }
  }
};

EFI_REST_JSON_STRUCTURE_PROTOCOL *mRestJsonStructureProt = NULL;

/**
  This function gets the string of revision number.
  
  @param[in]    Str             Odata.type string.
  @param[in]    StrIndex        Current string index. 
  @param[in]    OdataTypeStrLen Odata.type string length
   
  @retval != 0 Number found.
  @retval 0    Number not found.

**/
UINTN
GetOdataTypeVersionNum (CHAR8 *Str, UINTN *StrIndex, UINTN OdataTypeStrLen)
{
  UINTN NumIndex;
  UINTN Index;

  Index = *StrIndex;
  while (Str[Index] < 0x30 || Str[Index] > 0x39) {
    Index ++;
    if (OdataTypeStrLen < Index) {
      return 0;
    }
  };
  NumIndex = Index;
  while (Str [Index] != '.' && Str [Index] != '_') {
    Index ++;
    if (OdataTypeStrLen < Index) {
      return 0;
    }
  };
  Str [Index] = 0;
  *StrIndex = Index;
  return NumIndex;
}

/**
  This function checks if the given JSON property supported by this 
  Redfish JSON to C structure convertor.
  
  @param[in]    ResoruceRaw      Given JSON property.
   
  @retval EFI_SUCCESS
  @retval Others

**/
BOOLEAN
CheckSupportedSchema (IN CHAR8 *ResoruceRaw)
{
  json_t *TempJsonObj;
  json_t *JsonObjReturned;
  CHAR8 *TempChar;
  UINTN StrIndex;
  UINTN StrMajorIndex;
  UINTN StrMinorIndex;
  UINTN StrErrataIndex;
  UINTN OdataTypeStrLen;

  JsonObjReturned = json_loads(ResoruceRaw, 0, NULL);
  TempJsonObj = json_object_get(JsonObjReturned, "@odata.type");
  if (TempJsonObj == NULL) {
    goto Error;
  }
  TempChar = (CHAR8 *)json_string_value(TempJsonObj);
  OdataTypeStrLen = AsciiStrLen(TempChar);
  //
  // Validate odata.type
  //
  if (OdataTypeStrLen < AsciiStrLen(mResourceTypeStr)) {
    goto Error;
  }
 
  if (CompareMem ((VOID *)TempChar, (VOID *)mResourceTypeStr, AsciiStrLen(mResourceTypeStr)) != 0) {
    goto Error;
  }
  StrIndex = AsciiStrLen(mResourceTypeStr);
  if (TempChar [StrIndex] != '.' ) {
    goto Error;
  }
  StrIndex ++;
  if (OdataTypeStrLen < StrIndex) {
    goto Error;
  }
  if (!IsRevisonController) {
    //
    // No revision controllerd.
    //
    return TRUE;
  }
  
  //
  // Check major revision.
  //
  StrMajorIndex = GetOdataTypeVersionNum (TempChar, &StrIndex, OdataTypeStrLen);
  if (StrMajorIndex == 0) {
    goto Error;
  }

  //
  // Check minor revision.
  //
  StrMinorIndex = GetOdataTypeVersionNum (TempChar, &StrIndex, OdataTypeStrLen);
  if (StrMajorIndex == 0) {
    goto Error;
  }
  //
  // Check errata revision.
  //
  StrErrataIndex = GetOdataTypeVersionNum (TempChar, &StrIndex, OdataTypeStrLen);
  if (StrMajorIndex == 0) {
    goto Error;
  }
  if ((AsciiStrCmp(TempChar + StrMajorIndex, ResourceInterP[0].RestResourceInterp.NameSpace.MajorVersion) == 0) && 
      (AsciiStrCmp(TempChar + StrMinorIndex, ResourceInterP[0].RestResourceInterp.NameSpace.MinorVersion) == 0) &&
      (AsciiStrCmp(TempChar + StrErrataIndex, ResourceInterP[0].RestResourceInterp.NameSpace.ErrataVersion) == 0)) {
    json_decref(JsonObjReturned);
    return TRUE;
  }
Error:;
  json_decref(JsonObjReturned);
  return FALSE;
}

/**
  This function sets the structure of givin JSON resource in text format through
  supported Redfish schema interpreter.
  
  @param[in]    This              EFI_REST_JSON_STRUCTURE_PROTOCOL instance. 
  @param[in]    RsrcTypeIdentifier  Resource type identifier.
  @param[in]    ResoruceRaw       Given Restful resource.
  @param[in]    PropertyName      Name of property defined in the data type to retrieve.
  @param[out]   InterpProp        Property interpreted from given ResoruceRaw.
   
  @retval EFI_SUCCESS
  @retval Others

**/
EFI_STATUS
EFIAPI
DriveToStruct (
  IN EFI_REST_JSON_STRUCTURE_PROTOCOL         *This,
  IN EFI_REST_JSON_RESOURCE_TYPE_IDENTIFIER   *RsrcIdentifier OPTIONAL,
  IN CHAR8                                    *ResoruceRaw,
  IN CHAR8                                    *PropertyName OPTIONAL,
  OUT EFI_REST_JSON_STRUCTURE_HEADER          **InterpProp
)
{
  EFI_REDFISH_DRIVE_V1_6_5 *DriveV1_6_5;
  EFI_REDFISH_DRIVE_V1_6_5_CS *DriveV1_6_5Cs;
  EFI_REST_JSON_STRUCTURE_HEADER *RestIntrpHeader;
  CHAR8 *ResourceTypeMajorVersion;
  CHAR8 *ResourceTypeMinorVersion;
  CHAR8 *ResourceTypeErrataVersion;
  EFI_STATUS Status;

  if (ResoruceRaw == NULL || (RsrcIdentifier != NULL && RsrcIdentifier->NameSpace.ResourceTypeName == NULL)) {
    return EFI_INVALID_PARAMETER;
  }
  if (RsrcIdentifier == NULL ||
      (RsrcIdentifier != NULL && 
      (RsrcIdentifier->NameSpace.MajorVersion == NULL ||
       RsrcIdentifier->NameSpace.MinorVersion == NULL ||
       RsrcIdentifier->NameSpace.ErrataVersion == NULL))
       ) {
    //
    // Support revision determination.
    //
    if (!CheckSupportedSchema (ResoruceRaw)) {
      return EFI_UNSUPPORTED;
    }
  } else if ((AsciiStrCmp (RsrcIdentifier->NameSpace.MajorVersion, "1") != 0) ||
             (AsciiStrCmp (RsrcIdentifier->NameSpace.MinorVersion, "6") != 0) ||
             (AsciiStrCmp (RsrcIdentifier->NameSpace.ErrataVersion, "5") != 0) ||
             (AsciiStrCmp (RsrcIdentifier->NameSpace.ResourceTypeName, "Drive") != 0)) {
    return EFI_UNSUPPORTED;
  }

  Status = (EFI_STATUS)Json_Drive_V1_6_5_To_CS (ResoruceRaw, &DriveV1_6_5Cs);
  if (EFI_ERROR (Status)){
    return Status;
  }
  DriveV1_6_5 = (EFI_REDFISH_DRIVE_V1_6_5 *)AllocateZeroPool (
                        sizeof (EFI_REDFISH_DRIVE_V1_6_5));
  if (DriveV1_6_5 == NULL){
    return EFI_OUT_OF_RESOURCES;
  }
  RestIntrpHeader = (EFI_REST_JSON_STRUCTURE_HEADER *)DriveV1_6_5;
  DriveV1_6_5->Drive = DriveV1_6_5Cs;
  ResourceTypeMajorVersion = "1";
  ResourceTypeMinorVersion = "6";
  ResourceTypeErrataVersion = "5";
  //
  // Set header.
  //
  RestIntrpHeader->JsonRsrcIdentifier.NameSpace.ResourceTypeName = (CHAR8 *)AllocatePool (AsciiStrSize ("Drive"));
  AsciiStrCpyS (RestIntrpHeader->JsonRsrcIdentifier.NameSpace.ResourceTypeName, AsciiStrSize ("Drive"), "Drive");
  RestIntrpHeader->JsonRsrcIdentifier.NameSpace.MajorVersion = (CHAR8 *)AllocatePool (AsciiStrSize (ResourceTypeMajorVersion));
  AsciiStrCpyS (RestIntrpHeader->JsonRsrcIdentifier.NameSpace.MajorVersion, AsciiStrSize (ResourceTypeMajorVersion), ResourceTypeMajorVersion);
  RestIntrpHeader->JsonRsrcIdentifier.NameSpace.MinorVersion = (CHAR8 *)AllocatePool (AsciiStrSize (ResourceTypeMinorVersion));
  AsciiStrCpyS (RestIntrpHeader->JsonRsrcIdentifier.NameSpace.MinorVersion, AsciiStrSize (ResourceTypeMinorVersion), ResourceTypeMinorVersion);
  RestIntrpHeader->JsonRsrcIdentifier.NameSpace.ErrataVersion = (CHAR8 *)AllocatePool (AsciiStrSize (ResourceTypeErrataVersion));
  AsciiStrCpyS (RestIntrpHeader->JsonRsrcIdentifier.NameSpace.ErrataVersion, AsciiStrSize (ResourceTypeErrataVersion), ResourceTypeErrataVersion);
  RestIntrpHeader->JsonRsrcIdentifier.DataType = (CHAR8 *)AllocatePool (AsciiStrSize ("Drive"));
  AsciiStrCpyS (RestIntrpHeader->JsonRsrcIdentifier.DataType, AsciiStrSize ("Drive"), "Drive");
  *InterpProp = RestIntrpHeader;
  return EFI_SUCCESS;
}


/**
  The wrapper function of DriveToStruct which invokes **RESOURCE_TYPE**!ToStruct
  with additional parameter "PropertyName".
  
  @param[in]    This              EFI_REST_JSON_STRUCTURE_PROTOCOL instance. 
  @param[in]    RsrcTypeIdentifier  Resource type identifier.
  @param[in]    ResoruceRaw       Given Restful resource.
  @param[out]   InterpProp        Property interpreted from given ResoruceRaw.
   
  @retval EFI_SUCCESS
  @retval Others

**/
EFI_STATUS
EFIAPI
DriveToStructWrapper (
  IN EFI_REST_JSON_STRUCTURE_PROTOCOL         *This,
  IN EFI_REST_JSON_RESOURCE_TYPE_IDENTIFIER   *RsrcIdentifier OPTIONAL,
  IN CHAR8                                    *ResoruceRaw,
  OUT EFI_REST_JSON_STRUCTURE_HEADER          **InterpProp
)
{
  return DriveToStruct (
			  This,
			  RsrcIdentifier,
			  ResoruceRaw,
			  NULL,
			  InterpProp
			  );
}

/**
  This function returns JSON property in text format for the given structure through
  supported Restful data interpreter.
  
  @param[in]    This            EFI_REST_JSON_STRUCTURE_PROTOCOL instance. 
  @param[in]    InterpProp      Given Restful resource.
  @param[out]   ResoruceRaw     Resource in RESTfuls service oriented property interpreted from given ResoruceRaw.
                                Caller has to release the memory allocated for ResoruceRaw using DestoryJson function.

  @retval EFI_SUCCESS
  @retval Others

**/
EFI_STATUS
EFIAPI
DriveToJson(
  IN EFI_REST_JSON_STRUCTURE_PROTOCOL *This,
  IN EFI_REST_JSON_STRUCTURE_HEADER *InterpProp,
  OUT CHAR8 **ResoruceRaw
)
{
  if (InterpProp == NULL || ResoruceRaw == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  return (EFI_STATUS)CS_To_Drive_V1_6_5_JSON (*((EFI_REDFISH_DRIVE_V1_6_5_CS **)((UINT8 *)InterpProp + sizeof (EFI_REST_JSON_STRUCTURE_HEADER))), ResoruceRaw);  
}

/**
  This function destory structure retunred in DriveToStruct.
  
  @param[in]    This                EFI_REST_JSON_STRUCTURE_PROTOCOL instance. 
  @param[in]    InterpProp          Given Restful resource.

  @retval EFI_SUCCESS
  @retval Others

**/
EFI_STATUS
EFIAPI
DriveDestoryStruct(
  IN EFI_REST_JSON_STRUCTURE_PROTOCOL   *This,
  IN EFI_REST_JSON_STRUCTURE_HEADER  *InterpProp
)
{
  EFI_REDFISH_DRIVE_V1_6_5 *DriveV1_6_5;
  
  DriveV1_6_5 = (EFI_REDFISH_DRIVE_V1_6_5 *)InterpProp;
  DestroyDrive_V1_6_5_CS (DriveV1_6_5->Drive); 
  return EFI_SUCCESS;
}

/**
  This function destory JSON raw text returned from DriveFromStruct
  
  @param[in]    This                EFI_REST_JSON_STRUCTURE_PROTOCOL instance. 
  @param[in]    RsrcTypeIdentifier  Resource type identifier.  
  @param[in]    ResoruceRaw         JSON raw text.

  @retval EFI_SUCCESS
  @retval Others

**/
EFI_STATUS
EFIAPI
DriveDestoryJson(
  IN EFI_REST_JSON_STRUCTURE_PROTOCOL *This,
  IN EFI_REST_JSON_RESOURCE_TYPE_IDENTIFIER *RsrcIdentifier,  
  IN CHAR8 *ResoruceRaw
)
{
  if (ResoruceRaw == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  return (EFI_STATUS)DestroyDrive_V1_6_5_Json (ResoruceRaw);
}

/**
  This is the declaration of an EFI image entry point.

  @param  ImageHandle           The firmware allocated handle for the UEFI image.
  @param  SystemTable           A pointer to the EFI System Table.

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval Others                An unexpected error occurred.
**/
EFI_STATUS
EFIAPI
RedfishDrive_V1_6_5EntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS Status;
                      
  if (mRestJsonStructureProt == NULL) {
    Status = gBS->LocateProtocol(&gEfiRestJsonStructureProtocolGuid, NULL, (VOID **)&mRestJsonStructureProt);
    if ((EFI_ERROR (Status))) {
      return Status;
    }
  }
  Status = mRestJsonStructureProt->Register (
              mRestJsonStructureProt,
              ResourceInterP,
              DriveToStructWrapper,
              DriveToJson,
              DriveDestoryStruct
              );
  return Status;
}

/**
  This is the unload handle for Redfish discover module.

  Disconnect the driver specified by ImageHandle from all the devices in the handle database.
  Uninstall all the protocols installed in the driver entry point.

  @param[in] ImageHandle           The drivers' driver image.

  @retval    EFI_SUCCESS           The image is unloaded.
  @retval    Others                Failed to unload the image.

**/
EFI_STATUS
EFIAPI
RedfishDrive_V1_6_5Unload (
  IN EFI_HANDLE ImageHandle
  )
{
  //
  // Shall we implement Unregister() function in EFI JSON Structure Protocol?
  //
  return EFI_SUCCESS;
}
