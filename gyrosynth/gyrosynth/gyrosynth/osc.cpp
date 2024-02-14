/**********************************************************************
*          Copyright (c) 2023, Hogeschool voor de Kunsten Utrecht
*                      Utrecht, the Netherlands
*                          All rights reserved
***********************************************************************
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.
*  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************
*
*  File name     : osc.cpp
*  System name   : osc++ : Open Sound Control
*
*  Description   : C++ wrapper class for liblo
*
*
*  Author        : Marc_G
*  E-mail        : marcg@dinkum.nl
*
**********************************************************************/

#include "osc.hpp"


OSC::OSC()
{
}


OSC::~OSC()
{
  if(server) lo_server_thread_free(server);
  server=NULL;
}


/* _wrap_callback() is called by the OSC library and in turn calls the
 *    real callback of the object pointed to by user_data (!)
 *
 * For every message path the same callback is added, which means we need
 *  to separate the messages inside the callback
 */
int OSC::_wrap_callback(const char *path,const char *types,
          lo_arg **argv,int argc,void *data,void *user_data)
{
  return ((((OSC *) user_data)->realcallback(path,types,argv,argc)));
}


static void errorhandler(int num, const char* msg, const char* where)
{
  std::cout << "Error " << num << ": " << msg << std::endl;
  exit(1);
}


/*
 * start a new server in its own thread, waiting for data on the specified port
 */
void OSC::init(std::string serverport)
{
  server = lo_server_thread_new(serverport.c_str(),errorhandler);
}


/*
 *  link a method to a path. In reality, because we only have one callback,
 *   every method is added to the same callback and the messages are
 *   separated within the callback
 */
void OSC::set_callback(const char *path,const char *types)
{
  if(server) lo_server_thread_add_method(server,path,types,_wrap_callback,this);
}



void OSC::start()
{
  if(lo_server_thread_start(server) < 0)
  {
    std::cout << "Server failed to start" << std::endl;
    exit(1);
  }
}



void OSC::stop()
{
  if(server) lo_server_thread_free(server);
  server=NULL;
}



