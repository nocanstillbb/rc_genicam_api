/*
 * Roboception GmbH
 * Munich, Germany
 * www.roboception.com
 *
 * Copyright (c) 2017 Roboception GmbH
 * All rights reserved
 *
 * Author: Heiko Hirschmueller
 */

#ifndef RCGCAPI_CONFIG
#define RCGCAPI_CONFIG

#include <GenApi/GenApi.h>

#include <memory>
#include <string>
#include <vector>

/*
  This module provides convenience functions for setting and retrieving values
  from a GenICam nodemap.
*/

namespace rcg
{

/**
  Set the value of a boolean feature of the given nodemap.

  @param nodemap   Initialized nodemap.
  @param name      Name of feature.
  @param value     New value of feature.
  @param exception True if an error should be signaled via exception instead of
                   a return value.
  @return          True if value has been changed. False if feature does not
                   exist, has a different datatype or is not writable.
*/

bool setBoolean(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
                bool value, bool exception=false);

/**
  Set the value of an integer feature of the given nodemap.

  @param nodemap   Initialized nodemap.
  @param name      Name of feature.
  @param value     New value of feature.
  @param exception True if an error should be signaled via exception instead of
                   a return value.
  @return          True if value has been changed. False if feature does not
                   exist, has a different datatype or is not writable.
*/

bool setInteger(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
                int64_t value, bool exception=false);

/**
  Set the value of a float feature of the given nodemap.

  @param nodemap   Initialized nodemap.
  @param name      Name of feature.
  @param value     New value of feature.
  @param exception True if an error should be signaled via exception instead of
                   a return value.
  @return          True if value has been changed. False if feature does not
                   exist, has a different datatype or is not writable.
*/

bool setFloat(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
              double value, bool exception=false);

/**
  Set the value of an enumeration of the given nodemap.

  @param nodemap   Initialized nodemap.
  @param name      Name of feature.
  @param value     New value of feature.
  @param exception True if an error should be signaled via exception instead of
                   a return value.
  @return          True if value has been changed. False if feature does not
                   exist, has a different datatype or is not writable.
*/

bool setEnum(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
             const char *value, bool exception=false);

/**
  Set the value of a feature of the given nodemap. The datatype of the feature
  can be boolean, integer, float, enum or string. The given value will be
  converted depending on the datatype and representation of the feature, which
  can be hex, ip4v or mac for an integer feature.

  @param nodemap   Initialized nodemap.
  @param name      Name of feature.
  @param value     New value of feature.
  @param exception True if an error should be signaled via exception instead of
                   a return value.
  @return          True if value has been changed. False if feature does not
                   exist or is not writable or conversion failed.
*/

bool setString(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
               const char *value, bool exception=false);

/**
  Get the value of a boolean feature of the given nodemap.

  @param nodemap   Initialized nodemap.
  @param name      Name of feature.
  @param exception True if an error should be signaled via exception.
  @return          Value of boolean feature or false if the feature does not
                   exist, has a different datatype or is not readable.
*/

bool getBoolean(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
                bool exception=false);

/**
  Get the value of an integer feature of the given nodemap.

  @param nodemap   Initialized nodemap.
  @param name      Name of feature.
  @param vmin      Minimum value. A null poiter can be given if the value is
                   not required.
  @param vmax      Maximum value. A null poiter can be given if the value is
                   not required.
  @param exception True if an error should be signaled via exception.
  @return          Value of feature or 0 if the feature does not exist, has a
                   different datatype or is not readable. In this case vmin and
                   vmax will also be set to 0.
*/

int64_t getInteger(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
                   int64_t *vmin=0, int64_t *vmax=0, bool exception=false);

/**
  Get the value of a double feature of the given nodemap.

  @param nodemap   Initialized nodemap.
  @param name      Name of feature.
  @param vmin      Minimum value. A null poiter can be given if the value is
                   not required.
  @param vmax      Maximum value. A null poiter can be given if the value is
                   not required.
  @param exception True if an error should be signaled via exception.
  @return          Value of feature or 0 if the feature does not exist, has a
                   different datatype or is not readable. In this case vmin and
                   vmax will also be set to 0.
*/

double getFloat(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
                double *vmin=0, double *vmax=0, bool exception=false);

/**
  Get the value of an enumeration of the given nodemap.

  @param nodemap   Initialized nodemap.
  @param name      Name of feature.
  @param exception True if an error should be signaled via exception.
  @return          Value of enumeration or an empty string if the feature does
                   not exist, has a different datatype or is not readable.
*/

std::string getEnum(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
                    bool exception=false);

/**
  Get the current value and list of possible values of an enumeration of the
  given nodemap.

  @param nodemap   Initialized nodemap.
  @param name      Name of feature.
  @param list      List of possible values.
  @param exception True if an error should be signaled via exception.
  @return          Value of enumeration or an empty string if the feature does
                   not exist, has a different datatype or is not readable. In
                   this case, the returned list will be empty.
*/

std::string getEnum(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
                    std::vector<std::string> &list, bool exception=false);

/**
  Get the value of a feature of the given nodemap. The datatype of the feature
  can be boolean, integer, float, enum or string. The given value will be
  converted depending on the datatype and representation of the feature, which
  can be hex, ip4v or mac for an integer feature.

  @param nodemap   Initialized nodemap.
  @param name      Name of feature.
  @param exception True if an error should be signaled via exception.
  @return          Value or an empty string if the feature does not exist, has
                   a different datatype or is not readable.
*/

std::string getString(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
                      bool exception=false);

}

#endif