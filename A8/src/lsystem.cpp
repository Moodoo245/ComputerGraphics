
#include "lsystem.h"
#include <stack>
#include <memory>
#include <iostream>
#include <math.h>

/*
Provided utilities:

- Dice class (utils/misc.h)
	Produces random values uniformly distributed between 0 and 1
	Example:
		Dice d;
		double random_val = d.roll();

- write_string_to_file (utils/misc.h)
	Write string data into a text file.
	Example:
		write_string_to_file("ala ma kota!", "ala.txt");
*/

std::string LindenmayerSystemDeterministic::expandSymbol(unsigned char const& sym) {
	/*============================================================
		TODO 1.1
		For a given symbol in the sequence, what should it be replaced with after expansion?
	*/
	auto iter = rules.find(sym);
	if (iter != rules.end()) {
		return iter->second;
	}
	else {
		return {char(sym)};
	}

	//char rule = rules.find(sym);
	//return {char(rule)}; // this constructs string from char
	
	//============================================================

	/*
	You may find useful:
		map.find: Iterator to an element with key equivalent to key. If no such element is found, past-the-end (see end()) iterator is returned.
		http://en.cppreference.com/w/cpp/container/unordered_map/find
	*/
}

std::string LindenmayerSystem::expandOnce(std::string const& symbol_sequence) {
	/*============================================================
		TODO 1.2
		Perform one iteration of grammar expansion on `symbol_sequence`.
		Use the expandSymbol method
	*/
	std::string new_string;
	for(char sym : symbol_sequence) {
	    new_string  += expandSymbol(sym);
	}
	return new_string;

	//============================================================
}

std::string LindenmayerSystem::expand(std::string const& initial, uint32_t num_iters) {
	/*============================================================
		TODO 1.3
		Perform `num_iters` iterations of grammar expansion (use expandOnce)
	*/
	std::string symbol_sequence = initial;
	for(int i = 0; i < num_iters; i += 1 ) {
		symbol_sequence = expandOnce(symbol_sequence);
   	}

	return symbol_sequence;
	
	//============================================================
}

std::vector<Segment> LindenmayerSystem::draw(std::string const& symbols) {
	/*============================================================
		TODO 2.1
		Build line segments according to the sequence of symbols
		The initial position is (0, 0) and the initial direction is "up" (0, 1)
		Segment is std::pair<vec2, vec2>
	*/
	vec2 p = vec2(0, 0);
	vec2 f = vec2(0, 1);
	std::vector<Segment> Segments;
	std::stack<std::pair<vec2, vec2>> saved_states;

	for(char sym : symbols) {
	    if (sym=='+'){
	    	// rotates the direction f by the angle δ counter-clockwise

	    	float s = sin(rotation_angle_deg * (M_PI/180));
  			float c = cos(rotation_angle_deg * (M_PI/180));
  			//update direction
  			f[0] = f[0] * c - f[1] * s;
  			f[1] = f[0] * s + f[1] * c;
  			// normalize afterwards so every segment is length 1
  			f = normalize(f);
	    }
	    
	    else if (sym=='-'){
	    	// rotates the direction f by the angle δ counter-clockwise

	    	float s = sin(-rotation_angle_deg * (M_PI/180));
  			float c = cos(-rotation_angle_deg * (M_PI/180));
  			//update direction
  			f[0] = f[0] * c - f[1] * s;
  			f[1] = f[0] * s + f[1] * c;
  			// normalize afterwards so every segment is length 1
  			f = normalize(f);
	    }

	    else if (sym=='['){
	    	saved_states.push(std::make_pair(p, f));
	    }
	    else if (sym==']'){
	    	if(!saved_states.empty()) {
	    		p = saved_states.top().first;
	    		f = saved_states.top().second;
	    		saved_states.pop();
	    	} 
	    	else {
	    		std::cout << "saved_states stack is empty" << std::endl;
	    	}
	    }
	    
	    else {
	    	// F or any other symbol not listed above moves the pen forward (along the f direction) and draws a line segment of length 1
	    	vec2 new_pos = p + f;
	    	std::pair<vec2, vec2> segment (p, new_pos);
	    	Segments.push_back(segment);
	    	p = new_pos;
	    }
	}

	// returns an array of drawn line segments
	return {Segments};
	
	//============================================================
}

std::string LindenmayerSystemStochastic::expandSymbol(unsigned char const& sym) {
	/*============================================================
		TODO 4.1
		For a given symbol in the sequence, what should it be replaced with after expansion?
		(stochastic case)
	*/
	
	return {char(sym)};

	//============================================================
}

void LindenmayerSystemDeterministic::addRuleDeterministic(unsigned char sym, std::string const& expansion) {
	rules[sym] = expansion;
}

void LindenmayerSystemStochastic::addRuleStochastic(unsigned char sym, std::vector<StochasticRule> expansions_with_ps) {
	rules[sym] = expansions_with_ps;
}
