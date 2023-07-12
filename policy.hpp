#ifndef __DEMO_ECHO_SERVER_H
#define __DEMO_ECHO_SERVER_H

#include <cstdint>
#include <dbus-c++-1/dbus-c++/dbus.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <string>
#include "../server_path"
#include "../KETI-IBMC-hj/ibmc_proxy.h"
#include "../Feedback/feedback_proxy.h"
#include "../Monitor/monitor_proxy.h"
#include "../Energy/energy_proxy.h"
#include "../SSP/ssp_proxy.h"
#include "policy_adaptor.h"
static const char *POLICY_FILE_PATH="policy.json";
const std::string DEFAULT_POLICY_CONTENT = "{\"Power_consumption_policy\":\"enable\",\"Feedback_Engine_policy\":\"enable\"}";
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
  Ibmc_Proxy(DBus::Connection &connection, const char *path,
                   const char *name);
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
  Ssp_Proxy(DBus::Connection &connection, const char *path,
                   const char *name);
  ~Ssp_Proxy(){};
};
void connect_to_ibmc_server();
void connect_to_feedback_server();
void connect_to_monitor_server();
void connect_to_energy_server();
void connect_to_ssp_server();
void initialize_file();
void read_file();
void modify_policy(const std::string &policy_name, const std::string &status);
#endif  //__DEMO_ECHO_SERVER_H