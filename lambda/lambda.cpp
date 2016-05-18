#include <iostream>
#include <ostream>
#include <string>
#include <list>
#include <algorithm> // for_each

//#include <boost/optional>
// g++ lambda.cpp -std=c++11

namespace mdw
{
namespace bom
{

class Guest
{
public:
  // try ref here in construction to see what hapen
  explicit Guest(int iId, std::string iFirstName, std::string iLastName):id(iId),firstName(iFirstName),lastName(iLastName) {}
  //Guest() = default;

public:
  int id;
  std::string firstName;
  std::string lastName;

};

class HotelBooking {

public:
  explicit HotelBooking(const std::string& iConfirmationNumber):confirmationNumber(iConfirmationNumber){};

public:
  std::string confirmationNumber;
  std::list<Guest> guests;


};


// need to be brefore or forward declare
std::ostream& operator<<(std::ostream& os, Guest& g)
{
  os << g.id << ";" << g.firstName << ";" << g.lastName << std::endl;
  return os;
}

std::ostream& operator<<(std::ostream& os, HotelBooking b)
{
  os << "Reservation has confirmationNumber " << b.confirmationNumber << std::endl;
  os << "Guests are:" << std::endl;
  for_each(b.guests.begin(), b.guests.end(),
                                           [&] (mdw::bom::Guest& g)
                                           {
                                             os << g;
                                           }
                                         );
  return os;
}

}
}

namespace mdw
{
namespace tools
{

class IdComparator {
public:
  IdComparator(int iGuestIdToFind):_guestIdToFind(iGuestIdToFind) {};
public:
bool operator()(mdw::bom::Guest& iGuestToTest) {return iGuestToTest.id == _guestIdToFind;}

private:
  int _guestIdToFind;
};

}
}

namespace helper
{

void fillABooking(mdw::bom::HotelBooking& iHotelBooking) // ref also here, otherwise same as below updqte a copy of ref
{
  std::cout << "fillABooking begin" << std::endl;

  // not auto guest&
  auto& guests = iHotelBooking.guests; // ref is important here
                                       // if in main directly: otherwise guests vector inside hotelbooking is not updated but the local value! (see cout)
                                       // if in function as here: even worse because we are updating a copy of a ref -> core dump

  guests.push_back(mdw::bom::Guest(1, "coulombel", "sylvain"));
  guests.push_back(mdw::bom::Guest(2, "sarkozy", "nicolas"));
  guests.push_back(mdw::bom::Guest(3, "hollande", "francois"));
  guests.push_back(mdw::bom::Guest(4, "chirac", "jacques"));

  std::cout << iHotelBooking;
  std::cout << "fillABooking end" << std::endl;
}

}


int main()
{
  mdw::bom::HotelBooking hotelBooking("12345678");
  helper::fillABooking(hotelBooking);

   ////// JPR p46
   // find_if(InputIterator first, InputIterator last, UnaryPredicate pred)

   auto res = find_if(hotelBooking.guests.begin(), hotelBooking.guests.end(), mdw::tools::IdComparator(3));
   std::cout << *res;

   
}
