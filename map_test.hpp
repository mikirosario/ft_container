/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 07:20:48 by mrosario          #+#    #+#             */
/*   Updated: 2022/01/21 10:23:46 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testers.hpp"
#include <map>
#include "map.hpp"

static void	make_seed_map(std::map<std::string, std::string> & seed_map)
{
	seed_map.insert(std::make_pair("cuarenta y dos", "CUARENTA Y DOS: \t\t\tEl significado de la vida, el universo, y todo."));
	seed_map.insert(std::make_pair<std::string, std::string>("ordenador", "ORDENADOR: \t\t\t\tDispositivo que ordena e interpreta información almacenada en una serie de dígitos binarios."));
	seed_map.insert(std::make_pair<std::string, std::string>("piscina", "PISCINA: \t\t\t\tEscabechina de aspirantes a estudiantes."));
	seed_map.insert(std::make_pair<std::string, std::string>("arbol binario de rojos y negros", "ÁRBOL BINARIO DE ROJOS Y NEGROS: \tEstructura de datos incestuosa que reduce el tiempo de búsqueda a costa de hacer de tu padre el hijo de ti y de tu abuelo."));
	seed_map.insert(std::make_pair<std::string, std::string>("tig", "TIG: \t\t\t\t\tTrabajo de interés general."));
	seed_map.insert(std::make_pair<std::string, std::string>("lista enlazada", "LISTA ENLAZADA: \t\t\tEstructura de datos en la que cada elemento enlaza el siguiente y el anterior. Lentas en comparaciones e iteraciones, pero rápidas en inserciones y borrados."));
	seed_map.insert(std::make_pair<std::string, std::string>("array", "ARRAY: \t\t\t\t\tEstructura de datos contiguos en memoria RAM. Rápidos en comparaciones e iteraciones, pero lentos en inserciones y borrados."));
	seed_map.insert(std::make_pair<std::string, std::string>("marvin", "MARVIN: \t\t\t\tRobot cascarrabias."));
	seed_map.insert(std::make_pair<std::string, std::string>("norminette", "NORMINETTE: \t\t\t\tGuía de estilo que asegura que nadie podrá entender tu código."));
	seed_map.insert(std::make_pair<std::string, std::string>("cafe", "CAFÉ: \t\t\t\t\tBien de primera necesidad para la supervivencia elaborada a partir de granos de café molidos y agua."));
	seed_map.insert(std::make_pair<std::string, std::string>("agua", "AGUA: \t\t\t\t\tBien de primera necesidad por ser necesaria para la elaboración del café (véase: cafe)."));
	seed_map.insert(std::make_pair<std::string, std::string>("compilador", "COMPILADOR: \t\t\t\tÚnico profesor en activo de 42."));
}

template <typename Map_T>
void	map_test(void)
{
	typedef	typename Map_T::value_type	Pair;
	std::map<std::string, std::string>	seed_map;

	make_seed_map(seed_map);

	//DEFAULT CONSTRUCTOR
	PRINT	<< TXT_BYEL << "DEFAULT INSTANTIATION TEST" << END;
	Map_T		map_default;

	PRINT	<< TXT_NL << TXT_BYEL << "RANGE CONSTRUCTION TESTS" << END;
	//RANGE CONSTRUCTOR
	Map_T		map_range(seed_map.begin(), seed_map.end());

	//COPY CONSTRUCTOR
	PRINT	<< TXT_NL << TXT_BYEL << "COPY CONSTRUCTION TESTS" << END;
	Map_T		map_copy(map_range);

	//ASSIGNMENT OVERLOAD
	PRINT	<< TXT_NL << TXT_BYEL << "ASSIGNMENT OVERLOAD TESTS" << END;
	map_default = map_copy;

	//ITERATORS
	typename Map_T::iterator it = map_default.begin();
	typename Map_T::const_iterator end = map_default.end();
	for ( ; it != end; ++it)
		PRINT << it->second << TXT_NL;

	//REVERSE ITERATORS
	PRINT	<< TXT_NL << TXT_BYEL << "REVERSE ITERATOR TESTS" << END;
	typename Map_T::reverse_iterator rit = map_default.rbegin();
	typename Map_T::const_reverse_iterator rend = map_default.rend();	
	for ( ; rit != rend; ++rit)
		PRINT << rit->second << TXT_NL;

	//CAPACITY
	PRINT	<< TXT_NL << TXT_BYEL << "CAPACITY TESTS" << END;
	PRINT	<< map_default.empty() << TXT_NL;
	PRINT	<< map_default.size() << TXT_NL;

	//ACCESS
	PRINT	<< TXT_NL << TXT_BYEL << "ACCESS TESTS" << END;
	map_default["norminette"];
	map_default["aguafiestas"];
	map_default["miyamoto"] = "MIYAMOTO: \t\t\t\tEminencia de los videojuegos que descubrió que la constante gravitacional está más guapa como variable.";
	map_default["aguafiestas"] = "AGUAFIESTAS: \t\t\tSinónimo de Marvin (véase 'marvin').";

	//OPERATIONS
	PRINT	<< TXT_NL << TXT_BYEL << "OPERATIONS TESTS" << END;
	{
		typename Map_T::iterator mit = map_default.find("marvin");
		PRINT	<< mit->second << TXT_NL;
	}
	{
		typename Map_T::iterator mit = map_default.find("marvine");
		PRINT	<< (mit == map_default.end()) << TXT_NL;
	}

	PRINT	<< map_default.count("agua") << TXT_NL;
	PRINT	<< map_default.count("santana") << TXT_NL;
	{

	typename Map_T::iterator mit = map_default.lower_bound("marvin");
	PRINT	<< mit->second << TXT_NL;

	mit = map_default.lower_bound("marvinovich");
	PRINT	<< mit->second << TXT_NL;

	mit = map_default.lower_bound("aaaa");
	PRINT	<< mit->second << TXT_NL;

	mit = map_default.lower_bound("zzzz");
	PRINT	<< (mit == map_default.end()) << TXT_NL;

	mit = map_default.upper_bound("cafe");
	PRINT	<< mit->second << TXT_NL;

	mit = map_default.upper_bound("cafeteria");
	PRINT	<< mit->second << TXT_NL;

	mit = map_default.upper_bound("aaaa");
	PRINT	<< mit->second << TXT_NL;

	mit = map_default.upper_bound("zzzz");
	PRINT	<< (mit == map_default.end()) << TXT_NL;

	PRINT	<< map_default.equal_range("norminette").first->second << TXT_NL << map_default.equal_range("norminette").second->second << TXT_NL;
	}

	//INSERT
	PRINT	<< TXT_NL << TXT_BYEL << "INSERT TESTS" << END;
	map_default.insert(Pair("santana", "SANTANA: \t\t\t\tCanario estepario."));
	map_default.insert(map_default.lower_bound("alex"), Pair("alex", "ALEX: \t\t\t\tCien por cien NO FAKE!"));
	map_default.insert(map_default.lower_bound("a"), Pair("a", "A: \t\t\t\tPrimera letra del alafabeto latino."));
	map_default.insert(map_default.begin(), Pair("rorozco", "ROROZCO: \t\t\t\tDueña de la Playstation 4."));
	map_copy.insert(++map_default.begin(), --map_default.end());

	//ERASE
	PRINT	<< TXT_NL << TXT_BYEL << "ERASE TESTS" << TXT_NL;
	map_default.erase(map_default.begin()); //should erase 'a'
	map_default.erase("marvin"); //should erase 'marvin'
	{
		typename Map_T::iterator mit = map_default.find("norminette");
		typename Map_T::iterator mend = map_default.find("santana");
		map_default.erase(mit, mend); //should erase everything from norminette to before santana
	}

	//SWAP
	PRINT << TXT_NL << TXT_BYEL << "SWAP TEST (map_default <-> map_range)" << END;
	swap(map_default, map_range);

	//CLEAR
	PRINT << TXT_NL << TXT_BYEL << "CLEAR TEST (map_range)" << END;
	map_range.clear();

	//COMPARISON OBJECT
	PRINT	<< TXT_NL << TXT_BYEL << "COMP OBJECT TESTS" << END;
	{
		bool	my_res = map_default.value_comp()(*map_default.begin(), *map_default.begin());
		PRINT	<< std::boolalpha << my_res << END;
	}
	{
		bool	my_res = map_default.value_comp()(*map_default.begin(), *++map_default.begin());
		PRINT	<< std::boolalpha << my_res << END;
	}
}
