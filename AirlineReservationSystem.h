#pragma once

#include "utilFunctions.h"
#include "Graph.h"
#include "Date.h"
#include "Heap.h"

class AirlineReservationSystem
{
private:
	const static int INIFINITY = 999999999999;
	enum Criterion { TravelCost, TravelTime, Time };
	struct AirportData {
		string location;
		int hotelPricePerDay;
		AirportData()
		{
			location = "";
			hotelPricePerDay = INFINITY;
		}
		AirportData(const AirportData& obj)
		{
			*this = obj;
		}
		AirportData(string loc)
		{
			location = loc;
			hotelPricePerDay = INFINITY;
		}
		AirportData(string loc, int hot)
		{
			location = loc;
			hotelPricePerDay = hot;
		}
		const AirportData& operator=(const AirportData& obj)
		{
			if (this != &obj)
			{
				location = obj.location;
				hotelPricePerDay = obj.hotelPricePerDay;
			}
			return *this;
		}
		void display() const {
			cout << location << " " << hotelPricePerDay;
		}
		bool operator==(const AirportData& obj) const {
			if (this->location == obj.location)
			{
				return true;
			}
			return false;
		}
		~AirportData() {}
	};
	struct FlightData {
		Date dateOfTravel;
		int flyingTime; //in 24 hour mode, stores the hour of time only 
		int landingTime;
		int ticketPrice;
		string airlineName;
		FlightData()
		{
			flyingTime = 0;
			landingTime = 24;
			ticketPrice = INIFINITY;
			airlineName = "";
		}
		FlightData(const Date& doT, int ft, int lt, int tp, string an) :dateOfTravel(doT)
		{
			flyingTime = ft;
			landingTime = lt;
			ticketPrice = tp;
			airlineName = an;
		}
		const FlightData& operator=(const FlightData& obj)
		{
			dateOfTravel = obj.dateOfTravel;
			flyingTime = obj.flyingTime;
			landingTime = obj.landingTime;
			ticketPrice = obj.ticketPrice;
			airlineName = obj.airlineName;
			return *this;
		}
		FlightData(const FlightData& obj) :dateOfTravel(obj.dateOfTravel)
		{
			*this = obj;
		}
		bool operator < (const FlightData& obj)
		{
			if (dateOfTravel < obj.dateOfTravel) {
				return true;
			}
			else if (dateOfTravel == obj.dateOfTravel)
			{
				if (flyingTime < obj.flyingTime) {
					return true;
				}
				else if (flyingTime == obj.flyingTime)
				{
					if (landingTime < obj.landingTime) {
						return true;
					}
					else if (landingTime == obj.landingTime)
					{
						if (ticketPrice < obj.ticketPrice) {
							return true;
						}
						else if (ticketPrice == obj.ticketPrice)
						{
							if (airlineName < obj.airlineName || airlineName == obj.airlineName) {
								return true;
							}
							return false;
						}
						else {
							return false;
						}
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		void display() const
		{
			cout << dateOfTravel << " " << flyingTime << " " << landingTime << " " << ticketPrice << " " << airlineName;
		}
		~FlightData() {}
	};
	struct TravelDetails
	{
		AirportData origin;
		AirportData dest;
		FlightData flightDetails;
		Criterion sortBy;

		TravelDetails() {}
		TravelDetails(const TravelDetails& obj) {
			*this = obj;
		}
		const TravelDetails& operator=(const TravelDetails& obj)
		{
			origin = obj.origin;
			dest = obj.dest;
			flightDetails = obj.flightDetails;
			sortBy = obj.sortBy;
			return *this;
		}
		TravelDetails(AirportData origin, AirportData dest, FlightData flightData, Criterion sortBy = Time)
		{
			this->origin = origin;
			this->dest = dest;
			flightDetails = flightData;
			this->sortBy = sortBy;
		}
		bool operator<(const TravelDetails& obj) const
		{
			bool val = false;
			if (sortBy == Criterion::TravelCost)
			{
				val = flightDetails.ticketPrice < obj.flightDetails.ticketPrice;
			}
			else if (sortBy == Criterion::TravelTime)
			{
				val = flightDetails.landingTime - flightDetails.flyingTime < obj.flightDetails.landingTime - obj.flightDetails.flyingTime;
			}
			else if (sortBy == Criterion::Time)
			{
				if (flightDetails.dateOfTravel < obj.flightDetails.dateOfTravel)
				{
					val = true;
				}
				else if (flightDetails.dateOfTravel > obj.flightDetails.dateOfTravel)
				{
					val = false;
				}
				else
				{
					if (flightDetails.landingTime <= obj.flightDetails.flyingTime)
						val = true;
				}
			}
			return val;
		}
		bool operator>(const TravelDetails& obj) const
		{
			if (sortBy == Criterion::TravelCost)
			{
				return flightDetails.ticketPrice > obj.flightDetails.ticketPrice;
			}
			else if (sortBy == Criterion::TravelTime)
			{
				return flightDetails.landingTime - flightDetails.flyingTime > obj.flightDetails.landingTime - obj.flightDetails.flyingTime;
			}
			return false;
		}
		void display()const
		{
			origin.display();cout << " to ";dest.display();cout << " via ";flightDetails.display();
		}
		~TravelDetails() {}
	};
	struct TravelPath
	{
		Vector<TravelDetails> allFlightsToBeTaken;

		TravelPath() {}
		TravelPath(const TravelPath& obj)
		{
			*this = obj;
		}
		const TravelPath& operator=(const TravelPath& obj)
		{
			allFlightsToBeTaken = obj.allFlightsToBeTaken;
			return *this;
		}
		TravelPath(const Vector<TravelDetails>& obj)
		{
			allFlightsToBeTaken=obj;
		}
		bool operator<(const TravelPath& obj) const 
		{
			if (allFlightsToBeTaken[0].sortBy == Criterion::TravelCost)
			{

			}
			else if (allFlightsToBeTaken[0].sortBy == Criterion::TravelTime)
			{
				if (allFlightsToBeTaken[allFlightsToBeTaken.getSize() - 1].flightDetails.dateOfTravel - allFlightsToBeTaken[0].flightDetails.dateOfTravel < obj.allFlightsToBeTaken[obj.allFlightsToBeTaken.getSize() - 1].flightDetails.dateOfTravel - obj.allFlightsToBeTaken[0].flightDetails.dateOfTravel)
				{
					return true;
				}
				else if (allFlightsToBeTaken[allFlightsToBeTaken.getSize() - 1].flightDetails.dateOfTravel - allFlightsToBeTaken[0].flightDetails.dateOfTravel > obj.allFlightsToBeTaken[obj.allFlightsToBeTaken.getSize() - 1].flightDetails.dateOfTravel - obj.allFlightsToBeTaken[0].flightDetails.dateOfTravel)
				{
					return false;
				}
			}
			return true;
		}
		bool operator>(const TravelPath& obj) const
		{
			if (allFlightsToBeTaken[0].sortBy == Criterion::TravelCost)
			{

			}
			else if (allFlightsToBeTaken[0].sortBy == Criterion::TravelTime)
			{
				if (allFlightsToBeTaken[allFlightsToBeTaken.getSize() - 1].flightDetails.dateOfTravel - allFlightsToBeTaken[0].flightDetails.dateOfTravel < obj.allFlightsToBeTaken[obj.allFlightsToBeTaken.getSize() - 1].flightDetails.dateOfTravel - obj.allFlightsToBeTaken[0].flightDetails.dateOfTravel)
				{
					return false;
				}
				else if (allFlightsToBeTaken[allFlightsToBeTaken.getSize() - 1].flightDetails.dateOfTravel - allFlightsToBeTaken[0].flightDetails.dateOfTravel > obj.allFlightsToBeTaken[obj.allFlightsToBeTaken.getSize() - 1].flightDetails.dateOfTravel - obj.allFlightsToBeTaken[0].flightDetails.dateOfTravel)
				{
					return true;
				}
			}
			return true;
		}
		~TravelPath() {}
	};

	Graph<AirportData, TravelDetails> graph;
	ArrayBasedSet<string> allAirlines;

	void feedFileData(string flightsFilename, string hotelPricesFileName)
	{
		fstream obj;
		obj.open(hotelPricesFileName);
		if (!obj)
		{
			cout << "file opening failed\n";
			return;
		}
		while (!obj.eof())
		{
			char* temp = new char[250];
			obj.getline(temp, 250);
			Vector<string> lineTokens;
			split(' ', lineTokens, temp);
			graph.insertVertex(AirportData(lineTokens[0], string2int(lineTokens[1]))); //insert vertices to graph
		}
		obj.close();
		obj.open(flightsFilename);
		if (!obj)
		{
			cout << "file opening failed\n";
			return;
		}
		while (!obj.eof())
		{
			char* temp = new char[250];
			obj.getline(temp, 250);
			Vector<string> lineTokens;
			split(' ', lineTokens, temp);
			//retains hours only of flightTime and landingTime
			for (int i = 0; i < lineTokens[3].length(); i++)
			{
				if (lineTokens[3][i] == ':')
				{
					lineTokens[3][i] = 0;
					break;
				}
			}
			for (int i = 0; i < lineTokens[4].length(); i++)
			{
				if (lineTokens[4][i] == ':')
				{
					lineTokens[4][i] = 0;
					break;
				}
			}
			Vector<string> dateTokens;
			split('/', dateTokens, lineTokens[2]);
			AirportData o = AirportData(lineTokens[0]);
			AirportData d = AirportData(lineTokens[1]);
			Date(string2int(dateTokens[2])/*year*/, string2int(dateTokens[1])/*month*/, string2int(dateTokens[0])/*day*/);
			int f = string2int(lineTokens[3]);
			int g = string2int(lineTokens[4]);
			int c = string2int(lineTokens[5]);
			graph.insertEdge(AirportData(lineTokens[0]), //source
				AirportData(lineTokens[1]), //dest
				TravelDetails(AirportData(lineTokens[0]), AirportData(lineTokens[1]),
					FlightData(Date(string2int(dateTokens[2])/*year*/, string2int(dateTokens[1])/*month*/, string2int(dateTokens[0])/*day*/), //dateOfTravel
						string2int(lineTokens[3]), //flight starting time
						string2int(lineTokens[4]), //flight ending time
						string2int(lineTokens[5]), //cost of travel
						lineTokens[6]))); //airlineName
			allAirlines.addElement(lineTokens[6]);
		}

		graph.display();
		obj.close();
	}
	void menu()
	{
		int originChoice = -1;
		int destChoice = -1;
		bool isDateSpecified = false;
		Date date;
		int airlineChoice = -1;
		int criterionChoice = 0;
		int transitLocChoice = -1;
		int minTransitDur = -1;
		int maxTransitDur = -1;
		bool isFlightDirect = false;
		bool calculate = false;
		while (true) {
			cout << "Which of the following paramters do you want to specify?\n"
				<< "1. Origin\n"
				<< "2. Destination\n"
				<< "3. Date of Travel\n"
				<< "4. Airline\n"
				<< "5. Criterion\n"
				<< "6. Specify Transit Location\n"
				<< "7. Specify Minimum Transit Duration\n"
				<< "8. Specify Maximum Transit Duration\n"
				<< "9. Should flight be direct?\n"
				<< "10. I am done specifying, give me output\n"
				<< "11. Exit program\n"
				<< "Enter a number: ";
			int choice;
			cin >> choice;

			switch (choice)
			{
			case 1: //originChoice
			{
				Vector<AirportData> allAirports = graph.getAllVertex();
				for (int i = 0; i < allAirports.getSize(); i++)
				{
					cout << i + 1 << ". " << allAirports[i].location << endl;
				}
				cout << "Enter choice: ";
				cin >> originChoice;
				originChoice--;
				break;
			}
			case 2: //destChoice
			{
				Vector<AirportData> allAirports = graph.getAllVertex();
				for (int i = 0; i < allAirports.getSize(); i++)
				{
					cout << i + 1 << ". " << allAirports[i].location << endl;
				}
				cout << "Enter choice: ";
				cin >> destChoice;
				destChoice--;
				break;
			}
			case 3: //date
			{
			here:
				cout << "Enter day: ";
				int d, m, y;
				cin >> d;
				cout << "Enter month: ";
				cin >> m;
				cout << "Enter year: ";
				cin >> y;
				date = Date(y, m, d);
				cout << "Your preference is: " + date.toString() + "\nPress enter to confirm, enter any character to disagree: ";
				char* temp = new char[100];
				cin.getline(temp, 100);
				if (temp[0] != 0)
					goto here;
				isDateSpecified = true;
				break;
			}
			case 4: //airlineChoice
			{
				for (int i = 0; i < allAirlines.getSize(); i++)
				{
					cout << i + 1 << ". " << allAirlines[i] << endl;
				}
				cout << "Enter choice: ";
				cin >> airlineChoice;
				airlineChoice--;
				break;
			}
			case 5: //criterionChoice
			{
				cout << "Choose criteria:\n1. Minimal Travel Cost\n2. Minimal Travel Time\nEnter choice:";
				cin >> criterionChoice;
				criterionChoice--;
				break;
			}
			case 6: //transitLocChoice
			{
				Vector<AirportData> allAirports = graph.getAllVertex();
				for (int i = 0; i < allAirports.getSize(); i++)
				{
					cout << i + 1 << ". " << allAirports[i].location << endl;
				}
				cout << "Enter choice: ";
				cin >> transitLocChoice;
				transitLocChoice--;
				break;
			}
			case 7: //minTransitDur
			{
				cout << "Enter number of hours: ";
				cin >> minTransitDur;
				break;
			}
			case 8: //maxTransitDur
			{
				cout << "Enter number of hours: ";
				cin >> maxTransitDur;
				break;
			}
			case 9: //isFlightDirect
			{
				cout << "Enter Y for yes: ";
				char temp;
				cin >> temp;
				if (temp == 'Y' || temp == 'y')
					isFlightDirect = true;
				break;
			}
			case 10: //calculate paths
			{
				calculate = true;
				break;
			}
			case 11: //exit program
			{
				return;
			}
			}
			if (calculate)
			{
				getPlanAccordingToSpecifications(
					originChoice,
					destChoice,
					isDateSpecified,
					date,
					airlineChoice,
					static_cast<Criterion>(criterionChoice),
					transitLocChoice,
					minTransitDur,
					maxTransitDur,
					isFlightDirect
				);

				originChoice = -1;
				destChoice = -1;
				isDateSpecified = false;
				airlineChoice = -1;
				criterionChoice = 0;
				transitLocChoice = -1;
				minTransitDur = -1;
				maxTransitDur = -1;
				isFlightDirect = false;
				calculate = false;
			}
		}
	}
	void getPlanAccordingToSpecifications(int originIndex, int destIndex, bool isDateSpecified, Date date, int airlineIndex, Criterion criterion,
		int transitLocIndex, int minTransitDur, int maxTransitDur, bool isFlightDirect)
	{
		//Vector<TravelPath> possibleFlights;

		Vector<AirportData> allAirports = graph.getAllVertex();

		//get all paths from source to dest using depth first traversal
		Vector<Vector<Vector<TravelDetails>>> allPaths; //Vector<TravelDetails>: a single path from source to dest, 
														//Vector<Vector<TravelDetails>>: for each dest
														//Vector<Vector<TravelDetails>>>: for each source
		if (originIndex == -1)
		{
			if (destIndex == -1)
			{
				//all combinations of src and dest are taken
				for (int src = 0; src < allAirports.getSize(); src++)
				{
					for (int dest = 0; dest < allAirports.getSize();dest++)
					{
						if (src != dest)
						{
							Vector<Vector<TravelDetails>> allPossible = graph.getAllPaths(allAirports[src], allAirports[dest]);
							allPaths.addAtEnd(allPossible);
						}
					}
				}
			}
			else
			{
				//all sources and specified dest
				for (int src = 0; src < allAirports.getSize(); src++)
				{
					if (src != destIndex)
					{
						Vector<Vector<TravelDetails>> allPossible = graph.getAllPaths(allAirports[src], allAirports[destIndex]);
						allPaths.addAtEnd(allPossible);
					}
				}
			}
		}
		else
		{
			if (destIndex == -1)
			{
				//specified source and all dest taken
				for (int dest = 0; dest < allAirports.getSize();dest++)
				{
					if (originIndex != dest)
					{
						Vector<Vector<TravelDetails>> allPossible = graph.getAllPaths(allAirports[originIndex], allAirports[dest]);
						allPaths.addAtEnd(allPossible);
					}
				}
			}
			else
			{
				//specified source and specified dest
				Vector<Vector<TravelDetails>> allPossible = graph.getAllPaths(allAirports[originIndex], allAirports[destIndex]);
				allPaths.addAtEnd(allPossible);
			}
		}

		bool subtractDate = false;
		bool addDate = false;

	here:
		Heap<Vector<TravelDetails>> qualifyingPaths;

		for (int srcInd = 0; srcInd < allPaths.getSize(); srcInd++)
		{
			for (int destInd = 0; destInd < allPaths[srcInd].getSize(); destInd++)
			{
				Vector<TravelDetails> path = allPaths[srcInd][destInd];
				for (int flightNo = 0; flightNo < path.getSize(); flightNo++)
				{
					//path[flightNo].sortBy = criterion;
				}
				//the date of the firstFlight should be same as specified
				if (isDateSpecified)
				{
					if (allPaths[srcInd][destInd][0].flightDetails.dateOfTravel != date)
					{
						continue;
					}
				}
				//checking that all flights should be via specified airline (if any)
				if (airlineIndex >= 0)
				{
					int flightNo = 0;
					for (; flightNo < path.getSize(); flightNo++)
					{
						if (!(path[flightNo].flightDetails.airlineName == allAirlines[airlineIndex]))
						{
							break;
						}
					}
					if (flightNo != path.getSize())
					{
						continue;
					}
				}
				if (isFlightDirect)
				{
					if (path.getSize() > 1)
						continue;
				}
				qualifyingPaths.push((path));
			}
		}
		if (qualifyingPaths.size() == 0)
		{
			if (subtractDate == true)
			{
				if (addDate == false)
				{
					addDate = true;
					date = date + 2;
					cout << "No flights found on this date and the date before it so adding one date\n";
					goto here;
				}
			}
			else
			{
				date = date - 1;
				subtractDate = true;
				cout << "No flights found on this date so subtracting one date\n";
				goto here;
			}
		}
		cout << "-------------------------------------------------------------------------------------------------------------------------------------------\nQualifying Paths\n-------------------------------------------------------------------------------------------------------------------------------------------\n";
		while (qualifyingPaths.size() > 0)
		{
			Vector<TravelDetails> t = qualifyingPaths.top();
			qualifyingPaths.pop();
			for (int i = 0; i < t.getSize(); i++)
			{
				t[i].display();
				cout << " -> ";
			}
			cout << endl;
		}
	}

public:
	AirlineReservationSystem(string flightsFilename, string hotelPricesFileName)
	{
		feedFileData(flightsFilename, hotelPricesFileName);
		menu();
	}
};