#ifndef __DEMO_ECHO_SERVER_H
#define __DEMO_ECHO_SERVER_H

#include "energy_proxy.h"
#include "feedback_proxy.h"
#include "ibmc_proxy.h"
#include "monitor_proxy.h"
#include "ssp_proxy.h"
#include "common/server_path"
#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/stringbuffer.h"
#include "rapidjson/include/rapidjson/writer.h"
#include "policy_adaptor.h"
#include <cstdint>
#include <dbus-c++-1/dbus-c++/dbus.h>
#include <dbus-c++-1/dbus-c++/interface.h>
#include <dbus-c++-1/dbus-c++/message.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <math.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <thread>
#include <unistd.h>
#include <vector>
using namespace std;
static const char *POLICY_FILE_PATH = "policy.json";

class Policy_Adaptor : public org::freedesktop::keti::bmc::policy_adaptor,
                       public DBus::IntrospectableAdaptor,
                       public DBus::ObjectAdaptor

{
public:
  Policy_Adaptor(DBus::Connection &connection);
  int32_t policy_ibmc();
  int32_t policy_feedback();
  int32_t policy_monitor();
  int32_t policy_energy();
  int32_t policy_ssp();
};
class Ibmc_Proxy : public org::freedesktop::keti::bmc::ibmc_proxy,
                   public DBus::IntrospectableProxy,
                   public DBus::ObjectProxy {
public:
  Ibmc_Proxy(DBus::Connection &connection, const char *path, const char *name);
  ~Ibmc_Proxy(){};
};
class Feedback_Proxy : public org::freedesktop::keti::bmc::feedback_proxy,
                       public DBus::IntrospectableProxy,
                       public DBus::ObjectProxy {
public:
  Feedback_Proxy(DBus::Connection &connection, const char *path,
                 const char *name);
  ~Feedback_Proxy(){};
};
class Monitor_Proxy : public org::freedesktop::keti::bmc::monitor_proxy,
                      public DBus::IntrospectableProxy,
                      public DBus::ObjectProxy {
public:
  Monitor_Proxy(DBus::Connection &connection, const char *path,
                const char *name);
  ~Monitor_Proxy(){};
};
class Energy_Proxy : public org::freedesktop::keti::bmc::energy_proxy,
                     public DBus::IntrospectableProxy,
                     public DBus::ObjectProxy {
public:
  Energy_Proxy(DBus::Connection &connection, const char *path,
               const char *name);
  ~Energy_Proxy(){};
};
class Ssp_Proxy : public org::freedesktop::keti::bmc::ssp_proxy,
                  public DBus::IntrospectableProxy,
                  public DBus::ObjectProxy {
public:
  Ssp_Proxy(DBus::Connection &connection, const char *path, const char *name);
  ~Ssp_Proxy(){};
};

void policy_connect();
void make_policy_db();

void connect_to_ibmc_server();
void connect_to_feedback_server();
void connect_to_monitor_server();
void connect_to_energy_server();
void connect_to_ssp_server();

#endif //__DEMO_ECHO_SERVER_H