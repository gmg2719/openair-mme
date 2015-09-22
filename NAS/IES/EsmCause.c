/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under 
 * the Apache License, Version 2.0  (the "License"); you may not use this file
 * except in compliance with the License.  
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include "TLVEncoder.h"
#include "TLVDecoder.h"
#include "EsmCause.h"

int
decode_esm_cause (
  EsmCause * esmcause,
  uint8_t iei,
  uint8_t * buffer,
  uint32_t len)
{
  int                                     decoded = 0;

  if (iei > 0) {
    CHECK_IEI_DECODER (iei, *buffer);
    decoded++;
  }

  *esmcause = *(buffer + decoded);
  decoded++;
#if NAS_DEBUG
  dump_esm_cause_xml (esmcause, iei);
#endif
  return decoded;
}

int
encode_esm_cause (
  EsmCause * esmcause,
  uint8_t iei,
  uint8_t * buffer,
  uint32_t len)
{
  uint32_t                                encoded = 0;

  /*
   * Checking IEI and pointer
   */
  CHECK_PDU_POINTER_AND_LENGTH_ENCODER (buffer, ESM_CAUSE_MINIMUM_LENGTH, len);
#if NAS_DEBUG
  dump_esm_cause_xml (esmcause, iei);
#endif

  if (iei > 0) {
    *buffer = iei;
    encoded++;
  }

  *(buffer + encoded) = *esmcause;
  encoded++;
  return encoded;
}

void
dump_esm_cause_xml (
  EsmCause * esmcause,
  uint8_t iei)
{
  printf ("<Esm Cause>\n");

  if (iei > 0)
    /*
     * Don't display IEI if = 0
     */
    printf ("    <IEI>0x%X</IEI>\n", iei);

  printf ("    <Cause value>%u</Cause value>\n", *esmcause);
  printf ("</Esm Cause>\n");
}
