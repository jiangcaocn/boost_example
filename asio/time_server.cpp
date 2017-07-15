//
// Created by cj on 12/7/16.
//
#include <iostream>
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>

namespace asio = boost::asio;
using boost::asio::ip::tcp;
using boost::system::error_code;

void accept(tcp::acceptor &acceptor) {
	auto socket = std::make_shared<tcp::socket>(acceptor.get_io_service());
	acceptor.async_accept(*socket, [socket, &acceptor](const error_code &ec) {
		if (!!ec) {
			std::cout << "accept error: " << ec.message();
			return;
		}
		auto now = std::time(nullptr);
		auto data = std::string(std::ctime(&now));
		asio::async_write(*socket, asio::buffer(data), [socket](const error_code &ec, std::size_t nwrite) {
			if (!!ec) {
				std::cout << "write error: " << ec.message();
				return;
			}
			socket->shutdown(tcp::socket::shutdown_send);
		});
		accept(acceptor);
	});
}

int main() {
	std::cout << "start time server\n";

	asio::io_service service;
	tcp::endpoint endpoint{tcp::v4(), 8000};
	tcp::acceptor acceptor{service, endpoint};
	accept(acceptor);
	service.run();
}