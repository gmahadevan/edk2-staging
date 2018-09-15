/** @file
  This file defines the hob structure for FSP information.
  
  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php.

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __LOADER_FSP_INFO_GUID_H__
#define __LOADER_FSP_INFO_GUID_H__

extern EFI_GUID gLoaderFspInfoGuid;

typedef struct {  
  UINT8          Revision;
  UINT8          Reserved0[3];
  UINT32         FspsBase;
  VOID          *FspHobList;  
} LOADER_FSP_INFO;  
  
#endif
