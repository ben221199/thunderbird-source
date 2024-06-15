/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
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
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is Sun Microsystems,
 * Inc. Portions created by Sun are
 * Copyright (C) 1999 Sun Microsystems, Inc. All
 * Rights Reserved.
 *
 * Contributor(s): 
 */
#include "JNIEnvTests.h"
#include "AccessingStaticFields.h"

JNI_OJIAPITest(JNIEnv_SetStaticDoubleField_6)
{
  GET_JNI_FOR_TEST

  IMPLEMENT_GetStaticFieldID_METHOD("Test1", "static_name_double", "D");
  env->SetStaticDoubleField(clazz, fieldID, -100);
  printf("value = %Lf\n", env->GetStaticDoubleField(clazz, fieldID));
  if(env->GetStaticDoubleField(clazz, fieldID) == -100){
    return TestResult::PASS("SetStaticDoubleField(all correct, value == -100) set correct value to field");
  }else{
    return TestResult::FAIL("SetStaticDoubleField(all correct, value == -100) set incorrect value to field");
  }

}
