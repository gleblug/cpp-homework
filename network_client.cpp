#include <algorithm>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

#include <boost/asio.hpp>

class Client
{
private:

    using io_service = boost::asio::io_service;
    using tcp_endpoint = boost::asio::ip::tcp::endpoint;
    using tcp_socket = boost::asio::ip::tcp::socket;

public:

    Client(const std::string & client_name, const std::string & raw_ip_address, unsigned int port):
    m_client_name    (client_name),
    m_raw_ip_address (raw_ip_address),
    m_port           (port),
    m_exit_flag      (false),
    m_endpoint       (boost::asio::ip::address::from_string(raw_ip_address), port),
    m_socket         (m_service, m_endpoint.protocol())
    {

    }

    ~Client() noexcept = default;

public:

    auto run()
    {
        connect();

        boost::asio::write(m_socket, boost::asio::buffer(m_client_name));

        auto reader = std::thread(&Client::read, this);

        write();

        m_exit_flag = true;

        reader.join();
    }

private:

    void connect()
    {
        m_socket.connect(m_endpoint);
        std::cout << "Connected!" << std::endl;
    }

    void read()
    {
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

        send_message("server: " + message);
    }

    void send_message(const std::string & message)
    {
        std::cout << message << "\n";
    }
    
    void write()
    {
        for (
            std::string message;
            std::getline(std::cin, message) && message != last;
            boost::asio::write(m_socket, boost::asio::buffer(message))
            );

        boost::asio::write(m_socket, boost::asio::buffer("exit!"));
    }

private:

    inline static const std::string last = "exit!";

private:

    io_service    m_service;
    tcp_endpoint  m_endpoint;
    tcp_socket    m_socket;

    std::string   m_client_name;
    std::string   m_raw_ip_address;
    unsigned int  m_port;
    bool          m_exit_flag;

};

int main()
{
    system("chcp 1251");

    std::string raw_ip_address = "93.175.8.136";

    unsigned int port = 3333;

    try 
    {
        std::string nickname;
        std::cout << "\nEnter your nickname:\n";
        std::cin >> nickname;

        Client client(nickname, raw_ip_address, port);

        std::cout << "\nEnter any message you want to send to server\n";
        client.run();
    }
    catch (boost::system::system_error & e) 
    {
        std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

        system("pause");

        return e.code().value();
    }

    system("pause");

    return EXIT_SUCCESS;
}