#include "policy.hpp"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

DBus::BusDispatcher dispatcher;

Policy_Adaptor::Policy_Adaptor(DBus::Connection &connection)
    : DBus::ObjectAdaptor(connection, POLICY_SERVER_PATH) {}
int32_t Policy_Adaptor::policy_feedback() {
  cout << "feedback에서 온 요청 수행" << endl;
  return 0;
}
int32_t Policy_Adaptor::policy_ibmc() {
  cout << "ibmc에서 온 요청 수행" << endl;
  return 0;
}
int32_t Policy_Adaptor::policy_monitor() {
  cout << "monitor에서 온 요청 수행" << endl;
  return 0;
}
int32_t Policy_Adaptor::policy_energy() {
  cout << "energy에서 온 요청 수행" << endl;
  return 0;
}
int32_t Policy_Adaptor::policy_ssp() {
  cout << "ssp에서 온 요청 수행" << endl;
  return 0;
}
//-----------------------------Policy_Adaptor클래스끝-----------------------------
Ibmc_Proxy::Ibmc_Proxy(DBus::Connection &connection, const char *path,
                       const char *name)
    : DBus::ObjectProxy(connection, path, name) {}
//-----------------------------Ibmc_Proxy클래스끝-----------------------------
Feedback_Proxy::Feedback_Proxy(DBus::Connection &connection, const char *path,
                               const char *name)
    : DBus::ObjectProxy(connection, path, name) {}
//-----------------------------Feedback_Proxy클래스끝-----------------------------
Monitor_Proxy::Monitor_Proxy(DBus::Connection &connection, const char *path,
                             const char *name)
    : DBus::ObjectProxy(connection, path, name) {}
//-----------------------------Monitor_Proxy클래스끝-----------------------------
Energy_Proxy::Energy_Proxy(DBus::Connection &connection, const char *path,
                           const char *name)
    : DBus::ObjectProxy(connection, path, name) {}
//-----------------------------Energy_Proxy클래스끝-----------------------------
Ssp_Proxy::Ssp_Proxy(DBus::Connection &connection, const char *path,
                     const char *name)
    : DBus::ObjectProxy(connection, path, name) {}
//-----------------------------Ssp_Proxy클래스끝-----------------------------
void connect_to_ibmc_server() {
  DBus::BusDispatcher dispatcher;
  DBus::default_dispatcher = &dispatcher;
  DBus::Connection conn_n = DBus::Connection::SystemBus();
  Ibmc_Proxy dbus_adap_test =
      Ibmc_Proxy(conn_n, IBMC_SERVER_PATH, IBMC_SERVER_NAME);
  cout << "ibmc 서버와 연결 완료" << endl;
  dbus_adap_test.ibmc_policy();
}
void connect_to_feedback_server() {
  DBus::BusDispatcher dispatcher;
  DBus::default_dispatcher = &dispatcher;
  DBus::Connection conn_n = DBus::Connection::SystemBus();
  Feedback_Proxy dbus_adap_test =
      Feedback_Proxy(conn_n, FEEDBACK_SERVER_PATH, FEEDBACK_SERVER_NAME);
  cout << "feedback 서버와 연결 완료" << endl;
  dbus_adap_test.feedback_policy();
}
void connect_to_monitor_server() {
  DBus::BusDispatcher dispatcher;
  DBus::default_dispatcher = &dispatcher;
  DBus::Connection conn_n = DBus::Connection::SystemBus();
  Monitor_Proxy dbus_adap_test =
      Monitor_Proxy(conn_n, MONITOR_SERVER_PATH, MONITOR_SERVER_NAME);
  cout << "monitor 서버와 연결 완료" << endl;
  dbus_adap_test.monitor_policy();
}
void connect_to_energy_server() {
  DBus::BusDispatcher dispatcher;
  DBus::default_dispatcher = &dispatcher;
  DBus::Connection conn_n = DBus::Connection::SystemBus();
  Energy_Proxy dbus_adap_test =
      Energy_Proxy(conn_n, ENERGY_SERVER_PATH, ENERGY_SERVER_NAME);
  cout << "energy 서버와 연결 완료" << endl;
  dbus_adap_test.energy_policy();
}
void connect_to_ssp_server() {
  DBus::BusDispatcher dispatcher;
  DBus::default_dispatcher = &dispatcher;
  DBus::Connection conn_n = DBus::Connection::SystemBus();
  Ssp_Proxy dbus_adap_test =
      Ssp_Proxy(conn_n, SSP_SERVER_PATH, SSP_SERVER_NAME);
  cout << "ssp 서버와 연결 완료" << endl;
  dbus_adap_test.ssp_policy();
}


void run_policy_server() {
  std::cout << "  Policy Server Start " << std::endl;
  DBus::default_dispatcher = &dispatcher;

  DBus::Connection conn = DBus::Connection::SystemBus();
  conn.request_name(POLICY_SERVER_NAME);

  Policy_Adaptor server(conn);
  // 서버 유지
  dispatcher.enter();
}
void policy_connect() {
  string option = "", policy_name = "", status = "";
  string policy_option = "";
  while (true) {
    if (option == "ibmc") {
      cout << "Ibmc 서버 연결 요청" << endl;
      connect_to_ibmc_server();
    } else if (option == "feedback") {
      cout << "feedback 서버 연결 요청 " << endl;
      connect_to_feedback_server();
    } else if (option == "monitor") {
      cout << "monitor 서버 연결 요청 " << endl;
      connect_to_monitor_server();
    } else if (option == "energy") {
      cout << "energy 서버 연결 요청 " << endl;
      connect_to_energy_server();
    } else if (option == "ssp") {
      cout << "ssp 서버 연결 요청 " << endl;
      connect_to_ssp_server();
    } else {
      cout << "다시 입력하세요" << endl;
    }
  }
}

void niam(int sig) { dispatcher.leave(); }

