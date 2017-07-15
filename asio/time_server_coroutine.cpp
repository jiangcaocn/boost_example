//
// Created by cj on 12/9/16.
//
#include <iostream>
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>
#define BOOST_COROUTINE_NO_DEPRECATION_WARNING
#define BOOST_COROUTINES_NO_DEPRECATION_WARNING
#include <boost/asio/spawn.hpp>

namespace asio = boost::asio;
using boost::asio::ip::tcp;
using boost::system::error_code;

int main() {
    std::cout << "start time server using coroutine\n";

    asio::io_service service;
    tcp::endpoint endpoint{tcp::v4(), 8000};
    tcp::acceptor acceptor{service, endpoint};
    asio::spawn(service, [&acceptor](asio::yield_context yield) {
        for (;;) {
            std::cout << "to accept a connection... \n";
            auto socket = std::make_shared<tcp::socket>(acceptor.get_io_service());
            acceptor.async_accept(*socket, yield);
            asio::spawn(acceptor.get_io_service(), [socket](asio::yield_context yield) {
                auto now = std::time(nullptr);
                auto data = std::string(std::ctime(&now));
                asio::async_write(*socket, asio::buffer(data), yield);
                socket->shutdown(tcp::socket::shutdown_send);
            });
        }
    });
    service.run();
}
