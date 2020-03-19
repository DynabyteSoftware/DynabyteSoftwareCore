#pragma once
#include "AddressFamily.h"
#include "Internal/IConnection.h"
#include "Internal/IIPendpoint.h"

#pragma warning(push)
#pragma warning(disable:26812 6385 6255 6387 6258 6001 26495 26444 26451 28251)
#include "boost/asio/io_context.hpp"
#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/ip/udp.hpp"
#pragma warning(pop)

#include <variant>

namespace DynabyteSoftware
{
  namespace Networking
  {
    namespace BoostImplementation
    {
      class Connection : public virtual Internal::IConnection
      {
      public:
        #pragma region Types
        typedef std::variant < std::unique_ptr<boost::asio::ip::tcp::socket>,
                               std::unique_ptr<boost::asio::ip::udp::socket> > Socket;
        #pragma endregion

        #pragma region Constructors
        Connection(const Internal::IIPendpoint& endpoint);
        Connection(const std::shared_ptr<boost::asio::io_context>& context, TransportProtocol protocol,
                   AddressFamily addressFamily);
        #pragma endregion

        #pragma region Modifiers
        Socket& getSocket();
        #pragma endregion

        #pragma region IConnection
        virtual Connection& operator<<(const std::string& message) override;
        virtual Connection& operator>>(std::string& message) override;
        #pragma endregion
      private:
        #pragma region Variables
        std::shared_ptr<boost::asio::io_context> _context;
        Socket _socket;
        #pragma endregion

        #pragma region Constructors
        #pragma endregion
      };
    }
  }
}