#include "network.h"
#include "random.h"
#include <random>
#include <iostream>
// {} [] s w 2

void Network::resize(const size_t&  n)
{
	values.clear();
	std::vector<double> v(n,0.0); 
	RNG.normal(v);
	values = v;
	
}

bool Network::add_link(const size_t& a, const size_t& b) 
{	
	bool link;
	for(auto i : links){
		if ((i.first==a or i.first==b) and (i.second== a or i.second==b)){link=true;}
	}
	if ((a < values.size()) and (b < values.size()) and  (a >= 0) and (b >= 0) and (a!=b) and (link == false)){ 
	links.insert(std::pair<size_t,size_t>(a,b));
	links.insert(std::pair<size_t,size_t>(b,a));
	return true;
	}
	return false;
}

size_t Network::random_connect(const double& mean) //avec a la moyenne des degrees 
{ 
	links.clear();
	size_t compteur(0);
	for (size_t i(0) ; i<size() ; i++ ) {
		size_t nbr_degree(RNG.poisson(mean));
		std::vector<double> res(nbr_degree,0);
		RNG.uniform_double(res,0,size()-1);
		for(size_t k(0) ; k<nbr_degree;k++){
		add_link(values[i],res[k]);
		}
		compteur+= nbr_degree;
	}
	return compteur;
}

size_t Network::set_values(const std::vector<double>& val)
{
	if (val.size()>=values.size()){
		for ( size_t i(0); i<values.size(); ++i){values[i]=val[i];}
		return values.size();
	} else if (val.size()<values.size()){
		for ( size_t i(0); i<val.size(); ++i){values[i]=val[i];}
		return val.size();
	}
	return 0;
}

size_t Network::size() const { return values.size(); }

size_t Network::degree(const size_t &_n) const { return links.count(_n);}

double Network::value(const size_t &_n) const{ return values[_n]; }

std::vector<double> Network::sorted_values() const
{
	std::vector<double> sorted_values;
	sorted_values=values;
	std::sort(sorted_values.begin(),sorted_values.end(),std::greater<double>());
	return sorted_values;
}

std::vector<size_t> Network::neighbors(const size_t& n) const
{
	std::vector<size_t> neighbors;
	std::multimap<size_t,size_t>::const_iterator it;
	for (it = links.begin(); it!= links.end(); ++it){
		if(it->first==n){
			neighbors.push_back(it->second);
		}
	}
	return neighbors;
}

