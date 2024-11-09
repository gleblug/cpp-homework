#include <algorithm>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

#include <boost/asio.hpp>

class Server
{
private:

    using io_service   = boost::asio::io_service;
    using tcp_endpoint = boost::asio::ip::tcp::endpoint;
    using tcp_acceptor = boost::asio::ip::tcp::acceptor;
    using tcp_socket   = boost::asio::ip::tcp::socket;

public:

    Server(unsigned int port, int size):
    m_endpoint    (boost::asio::ip::address_v4::any(), port),
    m_acceptor    (m_service, m_endpoint.protocol()),
    m_socket      (m_service),
    m_port        (port),
    m_size        (size),
    m_exit_flag   (false)
    {
        m_acceptor.bind(m_endpoint);

        m_acceptor.listen(m_size);

        m_acceptor.accept(m_socket);

        get_client_name();
    }

    ~Server() noexcept
    {
        std::cout << "Server is destroyed\n";
    }

public:

    void run() 
    {
        auto reader = std::thread(&Server::read, this);

        write();

        m_exit_flag = true;

        reader.join();

        send_message(m_client_name + " left the server");
    }

private:

    void get_client_name()
    {
        boost::asio::streambuf buffer;

        boost::asio::read_until(m_socket, buffer, '!');

        std::istream input_stream(&buffer);
        std::getline(input_stream, m_client_name, '!');
    }

    void read()
    {
        send_message(m_client_name + " joined the server");

        while (!m_exit_flag)
        {
            read_data_until();
        }
    }

    void read_data_until()
    {
        boost::asio::streambuf buffer;

        boost::asio::read_until(m_socket, buffer, '!');

        std::string message;

        std::istream input_stream(&buffer);
        std::getline(input_stream, message, '!');

        if (message == last)
        {
            m_exit_flag = true;
            return;
        }

        send_message(m_client_name + ": " + message);
    }

    void send_message(const std::string & message)
    {
        std::cout << message << "\n";
    }

    void write()
    {
        for (
            std::string message;
            (!m_exit_flag) && std::getline(std::cin, message);
            boost::asio::write(m_socket, boost::asio::buffer(message))
        );
    }

private:

    inline static const std::string last = "exit";

private:

    std::string   m_client_name;

    io_service    m_service;
    tcp_endpoint  m_endpoint;
    tcp_acceptor  m_acceptor;
    tcp_socket    m_socket;
    unsigned int  m_port;
    int           m_size;

    bool          m_exit_flag; 

};

int main(int argc, char ** argv)
{
    int size = 30;

    auto port = 3333;

    try 
    {
        Server server(port, size);

        server.run();
    }
    catch (boost::system::system_error & e) 
    {
        std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

        return e.code().value();
    }

    return EXIT_SUCCESS;
}