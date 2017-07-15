//
// Created by cj on 12/5/16.
//
#include <iostream>
#include <chrono>
#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>

int main() {
	boost::asio::io_service io_service;
	boost::asio::steady_timer timer{io_service, std::chrono::seconds{2}};
	timer.async_wait([](const boost::system::error_code &){
		std::cout << "Hello boost steady timer s2 task 1!\n";
	});
	timer.async_wait([](const boost::system::error_code &){
		std::cout << "Hello boost steady timer s2 task 2!\n";
	});
	boost::asio::steady_timer timer2{io_service, std::chrono::seconds{4}};
	timer2.async_wait([](const boost::system::error_code &){
		std::cout << "Hello boost steady timer s4!\n";
	});

	io_service.run();
}