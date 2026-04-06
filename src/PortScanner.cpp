#include "PortScanner.hpp"
#include <boost/bind/bind.hpp>
#include <iostream>

const std::unordered_map<uint16_t, std::string> PortScanner::basicPorts = {
	{80, "HTTP"}, {443, "HTTPS"}, {22, "SSH"}, {21, "FTP"},
	{25, "SMTP"}, {53, "DNS"}, {110, "POP3"}, {143, "IMAP"},
	{3306, "MySQL"}, {5432, "PostgreSQL"}, {6379, "Redis"}
};

PortScanner::PortScanner(std::string& ip_address, std::string& port, int max_threads, std::uint8_t expiry_time) {
	set_options(ip_address, port, max_threads, expiry_time);
}

void PortScanner::set_options(std::string& domainName, std::string& port, int max_threads, std::uint8_t expiry_time) {
	this->domainName = domainName;
	this->MAX_THREADS = max_threads;
	this->expiry_time = expiry_time;
	parse_port(port);
}

void PortScanner::set_max_port(std::uint16_t port) {
	this->endPort = port;
}

void PortScanner::set_max_threads(int value) {
	this->MAX_THREADS = value;
}

void PortScanner::set_ip_address(std::string ip) {
	this->domainName = ip;
}

void PortScanner::set_expiry_time(std::uint8_t value) {
	this->expiry_time = value;
}

void PortScanner::parse_port(std::string& port) {
	size_t pos = port.find('-');
	if (pos != std::string::npos) {
		startPort = std::stoi(port.substr(0, pos));
		endPort = std::stoi(port.substr(pos + 1));
	} else {
		startPort = std::stoi(port);
		endPort = std::stoi(port);
	}
}

void PortScanner::setup_queue() {
	for (uint16_t i = startPort; i <= endPort; ++i) {
		q.push(i);
	}
}

void PortScanner::scan() {
	while (!q.empty()) {
		uint16_t port = q.front();
		q.pop();

		try {
			tcp::endpoint ep(boost::asio::ip::make_address(domainName), port);
			tcp::socket socket(io);
			socket.async_connect(ep, [this, port](const boost::system::error_code& ec) {
				if (!ec) {
					open_ports++;
					std::cout << GREEN << "[+] Port " << port << " is open" << RESET << std::endl;
				} else {
					closed_ports++;
				}
			});
		} catch (std::exception& e) {
			filtered_ports++;
		}
	}
}

void PortScanner::start() {
	setup_queue();
}

void PortScanner::run() {
	scan();
	io.run();
}