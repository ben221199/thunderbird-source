/* 
 * The contents of this file are subject to the Mozilla Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 * 
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 * 
 * The Original Code is the Netscape security libraries.
 * 
 * The Initial Developer of the Original Code is Netscape
 * Communications Corporation.  Portions created by Netscape are 
 * Copyright (C) 1994-2000 Netscape Communications Corporation.  All
 * Rights Reserved.
 * 
 * Contributor(s):
 * 
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License Version 2 or later (the
 * "GPL"), in which case the provisions of the GPL are applicable 
 * instead of those above.  If you wish to allow use of your 
 * version of this file only under the terms of the GPL and not to
 * allow others to use your version of this file under the MPL,
 * indicate your decision by deleting the provisions above and
 * replace them with the notice and other provisions required by
 * the GPL.  If you do not delete the provisions above, a recipient
 * may use your version of this file under either the MPL or the
 * GPL.
 */

#ifdef DEBUG
static const char CVS_ID[] = "@(#) $Source: /cvsroot/mozilla/security/nss/lib/pkix/src/RelativeDistinguishedName/Attic/MClear.c,v $ $Revision: 1.1 $ $Date: 2000/03/31 19:14:23 $ $Name: NSS_CLIENT_TAG $";
#endif /* DEBUG */

#ifndef PKIX_H
#include "pkix.h"
#endif /* PKIX_H */

/*
 * nss_pkix_RelativeDistinguishedName_Clear
 *
 * Wipes out cached data.
 */

NSS_IMPLEMENT PRStatus
nss_pkix_RelativeDistinguishedName_Clear
(
  NSSPKIXRelativeDistinguishedName *rdn
)
{
#ifdef NSSDEBUG
  if( PR_SUCCESS != nssPKIXRelativeDistinguishedName_verifyPointer(rdn) ) {
    return PR_FAILURE;
  }
#endif /* NSSDEBUG */

  if( (NSSBER *)NULL != rdn->ber ) {
    nss_ZFreeIf(rdn->ber->data);
    nss_ZFreeIf(rdn->ber);
  }

  if( (NSSDER *)NULL != rdn->der ) {
    nss_ZFreeIf(rdn->der->data);
    nss_ZFreeIf(rdn->der);
  }

  nss_ZFreeIf(rdn->utf8);

  return PR_SUCCESS;
}
