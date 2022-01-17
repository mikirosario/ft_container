/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:39:21 by mikiencolor       #+#    #+#             */
/*   Updated: 2022/01/17 20:42:39 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testers.hpp"
#include "ft_vector.hpp"

static void	make_seed_map(std::map<std::string, std::string> & seed_map)
{
	seed_map.insert(std::make_pair("cuarenta y dos", "CUARENTA Y DOS: \t\t\tEl significado de la vida, el universo, y todo."));
	seed_map.insert(std::make_pair<std::string, std::string>("ordenador", "ORDENADOR: \t\t\tDispositivo que ordena e interpreta información almacenada en una serie de dígitos binarios."));
	seed_map.insert(std::make_pair<std::string, std::string>("piscina", "PISCINA: \t\t\t\tEscabechina de aspirantes a estudiantes."));
	seed_map.insert(std::make_pair<std::string, std::string>("arbol binario de rojos y negros", "ÁRBOL BINARIO DE ROJOS Y NEGROS: \tEstructura de datos incestuosa que reduce el tiempo de búsqueda a costa de hacer de tu padre el hijo de ti y de tu abuelo."));
	seed_map.insert(std::make_pair<std::string, std::string>("tig", "TIG: \t\t\t\tTrabajo de interés general."));
	seed_map.insert(std::make_pair<std::string, std::string>("lista enlazada", "LISTA ENLAZADA: \t\t\tEstructura de datos en la que cada elemento enlaza el siguiente y el anterior. Lentas en comparaciones e iteraciones, pero rápidas en inserciones y borrados."));
	seed_map.insert(std::make_pair<std::string, std::string>("array", "ARRAY: \t\t\t\tEstructura de datos contiguos en memoria RAM. Rápidos en comparaciones e iteraciones, pero lentos en inserciones y borrados."));
	seed_map.insert(std::make_pair<std::string, std::string>("marvin", "MARVIN: \t\t\t\tRobot cascarrabias."));
	seed_map.insert(std::make_pair<std::string, std::string>("norminette", "NORMINETTE: \t\t\tGuía de estilo que asegura que nadie podrá entender tu código."));
	seed_map.insert(std::make_pair<std::string, std::string>("cafe", "CAFÉ: \t\t\t\tBien de primera necesidad para la supervivencia elaborada a partir de granos de café molidos y agua."));
	seed_map.insert(std::make_pair<std::string, std::string>("agua", "AGUA: \t\t\t\tBien de primera necesidad por ser necesaria para la elaboración del café (véase: cafe)."));
	seed_map.insert(std::make_pair<std::string, std::string>("compilador", "COMPILADOR: \t\t\tÚnico profesor en activo de 42."));
}

static void	make_seed_set(std::set<std::string> & seed_set)
{
	seed_set.insert("cuarenta y dos");
	seed_set.insert("ordenador");
	seed_set.insert("piscina");
	seed_set.insert("arbol binario de rojos y negros");
	seed_set.insert("tig");
	seed_set.insert("lista enlazada");
	seed_set.insert("array");
	seed_set.insert("marvin");
	seed_set.insert("norminette");
	seed_set.insert("cafe");
	seed_set.insert("agua");
	seed_set.insert("compilador");
}

int main(void)
{	
	std::map<std::string, std::string>	seed_map;
	std::set<std::string>				seed_set;
	ft::vector<bool>					results;

	make_seed_map(seed_map);
	make_seed_set(seed_set);

	//results.push_back(iterator_tests());
	results.push_back(my_veritable_vector());
	results.push_back(my_magnificent_map(seed_map));
	results.push_back(my_stupendous_stack());
	results.push_back(my_superlative_set(seed_set));		
	for (ft::vector<bool>::iterator it = results.begin(), end = results.end(); it != end; ++it)
	{
		if (*it == true)
			PRINT << TXT_BGRN "OK" << END;
		else
			PRINT << TXT_BRED "KO" << END;
	}
	system("leaks ft_container");
	return (0);
}
