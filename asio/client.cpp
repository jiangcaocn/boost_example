//
// Created by cj on 12/8/16.
//
#include <iostream>
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>

namespace asio = boost::asio;
using boost::asio::ip::tcp;
using boost::system::error_code;

void reader(const error_code &ec, std::size_t nread, std::array<char, 2048> &bytes, tcp::socket &socket) {
	if (!!ec) {
		std::cout << "read error: " << ec.message();
		return;
	}
	std::cout.write(bytes.data(), nread);
	socket.async_read_some(asio::buffer(bytes), [&socket, &bytes](const error_code &ec, std::size_t nread) {
		reader(ec, nread, bytes, socket);
	});
}

int main() {
	std::cout << "start client\n";

	asio::io_service service;

	tcp::resolver resolver{service};
	tcp::resolver::query q{"www.jd.com", "80"};
	tcp::socket socket{service};
	std::array<char, 2048> bytes;

	resolver.async_resolve(q, [&service, &socket, &bytes](const error_code &ec, tcp::resolver::iterator it) {
		if (!!ec) {
			std::cout << "resolve error: " << ec.message();
			return;
		}
		socket.async_connect(*it, [&socket, &bytes](const error_code &ec) {
			if (!!ec) {
				std::cout << "connect error: " << ec.message();
				return;
			}
			auto request = std::string("GET / HTTP/1.1\r\nHost:www.jd.com\r\n\r\n");
			asio::write(socket, asio::buffer(request));

			socket.async_read_some(asio::buffer(bytes), [&socket, &bytes](const error_code &ec, std::size_t nread) {
				reader(ec, nread, bytes, socket);
			});
		});
	});

	service.run();
}