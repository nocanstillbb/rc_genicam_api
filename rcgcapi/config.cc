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

#include "config.h"

#include <stdexcept>

namespace rcg
{

bool setBoolean(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
                bool value, bool exception)
{
  bool ret=false;

  GenApi::INode *node=nodemap->_GetNode(name);

  if (node != 0)
  {
    if (GenApi::IsWritable(node))
    {
      GenApi::IBoolean *val=dynamic_cast<GenApi::IBoolean *>(node);

      if (val != 0)
      {
        val->SetValue(value);
        ret=true;
      }
      else if (exception)
      {
        throw std::invalid_argument(std::string("Feature not boolean: ")+name);
      }
    }
    else if (exception)
    {
      throw std::invalid_argument(std::string("Feature not writable: ")+name);
    }
  }
  else if (exception)
  {
    throw std::invalid_argument(std::string("Feature not found: ")+name);
  }

  return ret;
}

bool setInteger(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
                int64_t value, bool exception)
{
  bool ret=false;

  GenApi::INode *node=nodemap->_GetNode(name);

  if (node != 0)
  {
    if (GenApi::IsWritable(node))
    {
      GenApi::IInteger *val=dynamic_cast<GenApi::IInteger *>(node);

      if (val != 0)
      {
        val->SetValue(value);
        ret=true;
      }
      else if (exception)
      {
        throw std::invalid_argument(std::string("Feature not integer: ")+name);
      }
    }
    else if (exception)
    {
      throw std::invalid_argument(std::string("Feature not writable: ")+name);
    }
  }
  else if (exception)
  {
    throw std::invalid_argument(std::string("Feature not found: ")+name);
  }

  return ret;
}

bool setFloat(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
              double value, bool exception)
{
  bool ret=false;

  GenApi::INode *node=nodemap->_GetNode(name);

  if (node != 0)
  {
    if (GenApi::IsWritable(node))
    {
      GenApi::IFloat *val=dynamic_cast<GenApi::IFloat *>(node);

      if (val != 0)
      {
        val->SetValue(value);
        ret=true;
      }
      else if (exception)
      {
        throw std::invalid_argument(std::string("Feature not float: ")+name);
      }
    }
    else if (exception)
    {
      throw std::invalid_argument(std::string("Feature not writable: ")+name);
    }
  }
  else if (exception)
  {
    throw std::invalid_argument(std::string("Feature not found: ")+name);
  }

  return ret;
}

bool setEnum(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
             const char *value, bool exception)
{
  bool ret=false;

  GenApi::INode *node=nodemap->_GetNode(name);

  if (node != 0)
  {
    if (GenApi::IsWritable(node))
    {
      GenApi::IEnumeration *val=dynamic_cast<GenApi::IEnumeration *>(node);

      if (val != 0)
      {
        GenApi::IEnumEntry *entry=val->GetEntryByName(value);

        if (entry != 0)
        {
          val->SetIntValue(entry->GetValue());

          return true;
        }
        else if (exception)
        {
          throw std::invalid_argument(std::string("Enumeration '")+name+
                                      "' does not contain: "+value);
        }
      }
      else if (exception)
      {
        throw std::invalid_argument(std::string("Feature not enumeration: ")+name);
      }
    }
    else if (exception)
    {
      throw std::invalid_argument(std::string("Feature not writable: ")+name);
    }
  }
  else if (exception)
  {
    throw std::invalid_argument(std::string("Feature not found: ")+name);
  }

  return ret;
}

bool setString(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
               const char *value, bool exception)
{
  bool ret=false;

  GenApi::INode *node=nodemap->_GetNode(name);

  if (node != 0)
  {
    if (GenApi::IsWritable(node))
    {
      switch (node->GetPrincipalInterfaceType())
      {
        case GenApi::intfIBoolean:
          {
            GenApi::IBoolean *p=dynamic_cast<GenApi::IBoolean *>(node);
            p->SetValue(std::stoi(std::string(value)));
          }
          break;

        case GenApi::intfIInteger:
          {
            GenApi::IInteger *p=dynamic_cast<GenApi::IInteger *>(node);

            switch (p->GetRepresentation())
            {
              case GenApi::HexNumber:
                p->SetValue(std::stoll(std::string(value), 0, 16));
                break;

              case GenApi::IPV4Address:
                {
                  int64_t ip=0;

                  std::stringstream in(value);
                  std::string elem;

                  for (int i=0; i<4; i++)
                  {
                    getline(in, elem, '.');
                    ip=(ip<<8)|(stoi(elem)&0xff);
                  }

                  p->SetValue(ip);
                }
                break;

              case GenApi::MACAddress:
                {
                  int64_t mac=0;

                  std::stringstream in(value);
                  std::string elem;

                  for (int i=0; i<4; i++)
                  {
                    getline(in, elem, ':');
                    mac=(mac<<8)|(stoi(elem, 0, 16)&0xff);
                  }

                  p->SetValue(mac);
                }
                break;

              default:
                p->SetValue(std::stoll(std::string(value)));
                break;
            }
          }
          break;

        case GenApi::intfIFloat:
          {
            GenApi::IFloat *p=dynamic_cast<GenApi::IFloat *>(node);
            p->SetValue(std::stof(std::string(value)));
          }
          break;

        case GenApi::intfIEnumeration:
          {
            GenApi::IEnumeration *p=dynamic_cast<GenApi::IEnumeration *>(node);
            GenApi::IEnumEntry *entry=p->GetEntryByName(value);

            if (entry != 0)
            {
              p->SetIntValue(entry->GetValue());
            }
            else if (exception)
            {
              throw std::invalid_argument(std::string("Enumeration '")+name+
                                          "' does not contain: "+value);
            }
          }
          break;

        case GenApi::intfIString:
          {
            GenApi::IString *p=dynamic_cast<GenApi::IString *>(node);
            p->SetValue(value);
          }
          break;

        default:
          if (exception)
          {
            throw std::invalid_argument(std::string("Feature of unknown datatype: ")+name);
          }
          break;
      }
    }
    else if (exception)
    {
      throw std::invalid_argument(std::string("Feature not writable: ")+name);
    }
  }
  else if (exception)
  {
    throw std::invalid_argument(std::string("Feature not found: ")+name);
  }

  return ret;
}

bool getBoolean(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
                bool exception)
{
  bool ret=false;

  GenApi::INode *node=nodemap->_GetNode(name);

  if (node != 0)
  {
    if (GenApi::IsReadable(node))
    {
      GenApi::IBoolean *val=dynamic_cast<GenApi::IBoolean *>(node);

      if (val != 0)
      {
        ret=val->GetValue();
      }
      else if (exception)
      {
        throw std::invalid_argument(std::string("Feature not boolean: ")+name);
      }
    }
    else if (exception)
    {
      throw std::invalid_argument(std::string("Feature not readable: ")+name);
    }
  }
  else if (exception)
  {
    throw std::invalid_argument(std::string("Feature not found: ")+name);
  }

  return ret;
}

int64_t getInteger(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
                   int64_t *vmin, int64_t *vmax, bool exception)
{
  int64_t ret=0;

  if (vmin != 0) *vmin=0;
  if (vmax != 0) *vmax=0;

  GenApi::INode *node=nodemap->_GetNode(name);

  if (node != 0)
  {
    if (GenApi::IsReadable(node))
    {
      GenApi::IInteger *val=dynamic_cast<GenApi::IInteger *>(node);

      if (val != 0)
      {
        ret=val->GetValue();

        if (vmin != 0) *vmin=val->GetMin();
        if (vmax != 0) *vmax=val->GetMax();
      }
      else if (exception)
      {
        throw std::invalid_argument(std::string("Feature not integer: ")+name);
      }
    }
    else if (exception)
    {
      throw std::invalid_argument(std::string("Feature not readable: ")+name);
    }
  }
  else if (exception)
  {
    throw std::invalid_argument(std::string("Feature not found: ")+name);
  }

  return ret;
}

double getFloat(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
                double *vmin, double *vmax, bool exception)
{
  double ret=0;

  if (vmin != 0) *vmin=0;
  if (vmax != 0) *vmax=0;

  GenApi::INode *node=nodemap->_GetNode(name);

  if (node != 0)
  {
    if (GenApi::IsReadable(node))
    {
      GenApi::IFloat *val=dynamic_cast<GenApi::IFloat *>(node);

      if (val != 0)
      {
        ret=val->GetValue();

        if (vmin != 0) *vmin=val->GetMin();
        if (vmax != 0) *vmax=val->GetMax();
      }
      else if (exception)
      {
        throw std::invalid_argument(std::string("Feature not float: ")+name);
      }
    }
    else if (exception)
    {
      throw std::invalid_argument(std::string("Feature not readable: ")+name);
    }
  }
  else if (exception)
  {
    throw std::invalid_argument(std::string("Feature not found: ")+name);
  }

  return ret;
}

std::string getEnum(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
                    bool exception)
{
  std::string ret;

  GenApi::INode *node=nodemap->_GetNode(name);

  if (node != 0)
  {
    if (GenApi::IsReadable(node))
    {
      GenApi::IEnumeration *val=dynamic_cast<GenApi::IEnumeration *>(node);

      if (val != 0)
      {
        ret=val->GetCurrentEntry()->GetSymbolic();
      }
      else if (exception)
      {
        throw std::invalid_argument(std::string("Feature not enumeration: ")+name);
      }
    }
    else if (exception)
    {
      throw std::invalid_argument(std::string("Feature not readable: ")+name);
    }
  }
  else if (exception)
  {
    throw std::invalid_argument(std::string("Feature not found: ")+name);
  }

  return ret;
}

std::string getEnum(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
                    std::vector<std::string> &list, bool exception)
{
  std::string ret;

  list.clear();

  GenApi::INode *node=nodemap->_GetNode(name);

  if (node != 0)
  {
    if (GenApi::IsReadable(node))
    {
      GenApi::IEnumeration *val=dynamic_cast<GenApi::IEnumeration *>(node);

      if (val != 0)
      {
        ret=val->GetCurrentEntry()->GetSymbolic();

        GenApi::StringList_t entry;
        val->GetSymbolics(entry);

        for (size_t i=0; i<entry.size(); i++)
        {
          list.push_back(std::string(entry[i]));
        }
      }
      else if (exception)
      {
        throw std::invalid_argument(std::string("Feature not enumeration: ")+name);
      }
    }
    else if (exception)
    {
      throw std::invalid_argument(std::string("Feature not readable: ")+name);
    }
  }
  else if (exception)
  {
    throw std::invalid_argument(std::string("Feature not found: ")+name);
  }

  return ret;
}

std::string getString(const std::shared_ptr<GenApi::CNodeMapRef> &nodemap, const char *name,
                      bool exception)
{
  std::ostringstream out;

  GenApi::INode *node=nodemap->_GetNode(name);

  if (node != 0)
  {
    if (GenApi::IsReadable(node))
    {
      switch (node->GetPrincipalInterfaceType())
      {
        case GenApi::intfIBoolean:
          {
            GenApi::IBoolean *p=dynamic_cast<GenApi::IBoolean *>(node);
            out << p->GetValue();
          }
          break;

        case GenApi::intfIInteger:
          {
            GenApi::IInteger *p=dynamic_cast<GenApi::IInteger *>(node);
            int64_t value=p->GetValue();

            switch (p->GetRepresentation())
            {
              case GenApi::HexNumber:
                out << std::hex << value;
                break;

              case GenApi::IPV4Address:
                 out << ((value>>24)&0xff) << '.' << ((value>>16)&0xff) << '.'
                     << ((value>>8)&0xff) << '.' << (value&0xff);
                 break;

              case GenApi::MACAddress:
                 out << std::hex << ((value>>32)&0xff) << ':' << ((value>>30)&0xff) << ':'
                                 << ((value>>24)&0xff) << ':' << ((value>>16)&0xff) << ':'
                                 << ((value>>8)&0xff) << ':' << (value&0xff);
                 break;

              default:
                out << value;
                break;
            }
          }
          break;

        case GenApi::intfIFloat:
          {
            GenApi::IFloat *p=dynamic_cast<GenApi::IFloat *>(node);
            out << p->GetValue();
          }
          break;

        case GenApi::intfIEnumeration:
          {
            GenApi::IEnumeration *p=dynamic_cast<GenApi::IEnumeration *>(node);
            out << p->GetCurrentEntry()->GetSymbolic();
          }
          break;

        case GenApi::intfIString:
          {
            GenApi::IString *p=dynamic_cast<GenApi::IString *>(node);
            out << p->GetValue();
          }
          break;

        default:
          if (exception)
          {
            throw std::invalid_argument(std::string("Feature of unknown datatype: ")+name);
          }
          break;
      }
    }
    else if (exception)
    {
      throw std::invalid_argument(std::string("Feature not readable: ")+name);
    }
  }
  else if (exception)
  {
    throw std::invalid_argument(std::string("Feature not found: ")+name);
  }

  return out.str();
}

}