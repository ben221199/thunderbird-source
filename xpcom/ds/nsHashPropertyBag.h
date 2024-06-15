/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Oracle Corporation code.
 *
 * The Initial Developer of the Original Code is
 *  Oracle Corporation
 * Portions created by the Initial Developer are Copyright (C) 2004
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Vladimir Vukicevic <vladimir.vukicevic@oracle.com>
 *   Christian Biesinger <cbiesinger@web.de>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef nsHashPropertyBag_h___
#define nsHashPropertyBag_h___

#include "nsCOMPtr.h"
#include "nsCOMArray.h"
#include "nsVoidArray.h"

#include "nsIWritablePropertyBag.h"
#include "nsIWritablePropertyBag2.h"
#include "nsInterfaceHashtable.h"

#undef  IMETHOD_VISIBILITY
#define IMETHOD_VISIBILITY NS_VISIBILITY_DEFAULT

class NS_COM nsHashPropertyBag : public nsIWritablePropertyBag
                               , public nsIWritablePropertyBag2
{
public:
    nsHashPropertyBag() { }
    virtual ~nsHashPropertyBag() {}

    nsresult Init();

    NS_DECL_ISUPPORTS

    NS_DECL_NSIPROPERTYBAG

    NS_DECL_NSIPROPERTYBAG2

    NS_DECL_NSIWRITABLEPROPERTYBAG

    NS_DECL_NSIWRITABLEPROPERTYBAG2

protected:
    // a hash table of string -> nsIVariant
    nsInterfaceHashtable<nsStringHashKey, nsIVariant> mPropertyHash;
};

#undef  IMETHOD_VISIBILITY
#define IMETHOD_VISIBILITY NS_VISIBILITY_HIDDEN

// Note: NS_NewHashPropertyBag returns a HPB that
// uses a non-thread-safe internal hash
extern "C" NS_COM nsresult
NS_NewHashPropertyBag(nsIWritablePropertyBag* *_retval);

#endif /* nsHashPropertyBag_h___ */
