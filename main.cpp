/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 13:39:21 by mikiencolor       #+#    #+#             */
/*   Updated: 2022/01/17 20:26:12 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testers.hpp"
#include "ft_vector.hpp"
#include <set>

int main(void)
{	
	std::map<std::string, std::string>	seed_map;
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

	std::set<std::string>				seed_set;
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

	ft::vector<bool>	results;
	

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

//debug

PRINT << '\n' << "QUECHTAPACHANDO" << std::endl;

		// ft::set<int> const st;
        // ft::set<int>::iterator it = st.begin(); // <-- no error, actually ! set allows for const_iterator => iterator conversion

        // std::list<std::string> lst;
        // unsigned int lst_size = 10;
        // for (unsigned int i = 0; i < lst_size; ++i)
        //         lst.push_back(std::string((lst_size - i), i + 65));
        // ft::set<std::string> st(lst.begin(), lst.end());
        // //printSize(st);

        // ft_erase(st, ++st.begin());

        // ft_erase(st, st.begin());
        // ft_erase(st, --st.end());

        // ft_erase(st, st.begin(), ++(++(++st.begin())));
        // ft_erase(st, --(--(--st.end())), --st.end());

        // st.insert("Hello");
        // st.insert("Hi there");
        // ft_erase(st, --(--(--st.end())), st.end());

        // st.insert("ONE");
        // st.insert("TWO");
        // st.insert("THREE");
        // st.insert("FOUR");
        // ft_erase(st, st.begin(), st.end());

        // std::list<char> lst;
        // unsigned int lst_size = 7;
        // for (unsigned int i = 0; i < lst_size; ++i)
        //         lst.push_back('a' + i);

        // ft::set<char> st(lst.begin(), lst.end()), st2;
        // ft::set<char>::iterator it;

        // lst.clear();
        
        // std::cout << st.size();
		// std::cout << st.empty();

        
        // st2 = st;
        

        // it = st.begin();
        // for (unsigned long int i = 3; i < 6; ++i)
        //         st.insert(i * 7);

        // std::cout << st2.size();
		// std::cout << st2.empty();
        

        // st2.clear();
        

        // ft::set<int> st;

        // ft::set<int>::iterator ite = st.begin();
        // *ite = 42; // < -- error as well ; T is always const, even with regular iterator


		// typedef ft::pair<int const, int>	Bleh;
		// std::list<Bleh> lst;
        // unsigned int lst_size = 7;
        // for (unsigned int i = 0; i < lst_size; ++i)
        //         lst.push_back(Bleh(lst_size - i, i));

        // ft::map<int, int> mp(lst.begin(), lst.end());
        // ft::map<int, int>::iterator it = mp.begin(), ite = mp.end();

        // ft::map<int, int> mp_range(it, --(--ite));
        // for (int i = 0; it != ite; ++it)
        //         it->second = ++i * 5;

        // it = mp.begin(); ite = --(--mp.end());
        // ft::map<int, int> mp_copy(mp);
        // for (int i = 0; it != ite; ++it)
        //         it->second = ++i * 7;




        // ft::vector<int> vct(lst.begin(), lst.end());
		// std::vector<int> svct(lst.begin(), lst.end());
        // for (ft::vector<int>::iterator it = vct.begin(), end = vct.end(); it != end; ++it)
		// 	PRINT << "MY VEC: " << *it << '\n';
		// for (std::vector<int>::iterator it = svct.begin(), end = svct.end(); it != end; ++it)
		// 	PRINT << "SU VEC: " << *it << '\n';

        // lst_it = lst.begin();
        // for (int i = 1; lst_it != lst.end(); ++i)
        //     *lst_it++ = i * 5;
        // vct.assign(lst.begin(), lst.end());
		// svct.assign(lst.begin(), lst.end());
		// for (ft::vector<int>::iterator it = vct.begin(), end = vct.end(); it != end; ++it)
		// 	PRINT << "MY VEC: " << *it << '\n';
		// for (std::vector<int>::iterator it = svct.begin(), end = svct.end(); it != end; ++it)
		// 	PRINT << "SU VEC: " << *it << '\n';

        // vct.insert(vct.end(), lst.rbegin(), lst.rend());
		// svct.insert(svct.end(), lst.rbegin(), lst.rend());
        // for (ft::vector<int>::iterator it = vct.begin(), end = vct.end(); it != end; ++it)
		// 	PRINT << "MY VEC: " << *it << '\n';
		// for (std::vector<int>::iterator it = svct.begin(), end = svct.end(); it != end; ++it)
		// 	PRINT << "SU VEC: " << *it << '\n';

//debug
	/*****/
	
	
// 	//size_t				i;
// 	ft::bintree<int>	ex1;
// 	ft::bintree<int>	ex2;

// 	//Esto tiene que funcionar :P
// 	// std::vector<int>	pepe;
// 	// int kevin[] = {1,2,3,4,5};
// 	// pepe.assign(kevin, kevin + 5);


// 	// std::vector<int> k (kevin, kevin + 5);

// 	// std::vector<int> std_quick_test;
// 	ft::vector<int>	quick_test;
// 	for(ft::vector<int>::const_iterator it = quick_test.begin(), end = quick_test.end(); it != end; ++it) {}
// 	//for (std::vector<int>::const_iterator it = std_quick_test.begin(), end = std_quick_test.end(); it != end; ++it) {}
// 	//DEFAULT CONSTRUCTOR
// 	PRINT << "MAP INSERT BY PAIR" << END;
// 	ft::map<std::string, std::string>	my_dictionary_default;
	
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("cuarenta y dos", "CUARENTA Y DOS: \t\t\tEl significado de la vida, el universo, y todo."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("ordenador", "ORDENADOR: \t\t\t\tDispositivo que ordena e interpreta información almacenada en una serie de dígitos binarios."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("piscina", "PISCINA: \t\t\t\tEscabechina de aspirantes a estudiantes."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("arbol binario de rojos y negros", "ÁRBOL BINARIO DE ROJOS Y NEGROS: \tEstructura de datos incestuosa que reduce el tiempo de búsqueda a costa de hacer de tu padre el hijo de ti y de tu abuelo."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("tig", "TIG: \t\t\t\t\tTrabajo de interés general."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("lista enlazada", "LISTA ENLAZADA: \t\t\tEstructura de datos en la que cada elemento enlaza el siguiente y el anterior. Lentas en comparaciones e iteraciones, pero rápidas en inserciones y borrados."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("array", "ARRAY: \t\t\t\t\tEstructura de datos contiguos en memoria RAM. Rápidos en comparaciones e iteraciones, pero lentos en inserciones y borrados."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("marvin", "MARVIN: \t\t\t\tRobot cascarrabias."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("norminette", "NORMINETTE: \t\t\t\tGuía de estilo que asegura que nadie podrá entender tu código."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("cafe", "CAFÉ: \t\t\t\t\tBien de primera necesidad para la supervivencia elaborada a partir de granos de café molidos y agua."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("agua", "AGUA: \t\t\t\t\tBien de primera necesidad por ser necesaria para la elaboración del café (véase: cafe)."));
// 	my_dictionary_default.insert(ft::make_pair<std::string, std::string>("compilador", "COMPILADOR: \t\t\t\tÚnico profesor en activo de 42."));
	
// 	for (ft::map<std::string, std::string>::iterator it = my_dictionary_default.begin(), end = my_dictionary_default.end(); it != end; ++it)
// 		PRINT << it->second << END;

// 	//COPY CONSTRUCTOR
// 	ft::map<std::string, std::string>	my_dictionary_copy(my_dictionary_default);
// 	for (ft::map<std::string, std::string>::const_iterator it = my_dictionary_copy.begin(), end = my_dictionary_copy.end(); it != end; ++it)
// 		PRINT << it->second << END;
// 	std::map<std::string, std::string>	std_dictionary;
// 	for (std::map<std::string, std::string>::const_iterator it = std_dictionary.begin(), end = std_dictionary.end(); it != end; ++it)
// 		PRINT << it->second << END;

// 	//RANGE CONSTRUCTOR
// 	ft::map<std::string, std::string>	my_dictionary_range(my_dictionary_default.begin(), my_dictionary_default.end());
// 	for (ft::map<std::string, std::string>::const_iterator it = my_dictionary_range.begin(), end = my_dictionary_range.end(); it != end; ++it)
// 		PRINT << it->second << END;
	
// 	//ASSIGN CONSTRUCTOR
// 	ft::map<std::string, std::string>	my_dictionary_assign;
// 	my_dictionary_assign = my_dictionary_default;
// 	for (ft::map<std::string, std::string>::const_iterator it = my_dictionary_assign.begin(), end = my_dictionary_assign.end(); it != end; ++it)
// 		PRINT << it->second << END;

// 	//CONST TEST
// 	// const ft::map<std::string, std::string>	my_dictionary_const(my_dictionary_default);
// 	// for (ft::map<std::string, std::string>::const_iterator it = my_dictionary_const.begin(), end = my_dictionary_const.end(); it != end; ++it)
// 	// 	PRINT << (it->second = "blah blah blah") << END;
// 	ft::map<std::string, std::string>	my_dictionary_no_const(my_dictionary_default);
// 	for (ft::map<std::string, std::string>::iterator it = my_dictionary_no_const.begin(), end = my_dictionary_no_const.end(); it != end; ++it)
// 		PRINT << (it->second = "blah blah blah") << END;
	



// 	// test2.insert("cuarenta y dos", 42);
// 	// test2.insert("uno", 1);
// 	// test2.insert("noventa y nueve
	
// 	// ft::map<std::string, std::string>	my_default_constructed_dictionary;
// 	// ft::map<std::string, std::string>	my_default_constructed_dictionary;
// 	// ft::map<std::string, std::string>	my_default_constructed_dictionary;
	

	

// 	typedef ft::bintree_pair<std::string, std::string>	Dictionary;
	
// 	Dictionary	test2;

// 	PRINT << std::boolalpha << "New bintree ex1 is empty: " << ex1.empty() << END;
// 	PRINT << "New bintree ex1 size: " << ex1.size() << END;

// 	ex1.insert(58);
// 	ex1.insert(26);
// 	ex1.insert(2);
// 	ex1.insert(42);
// 	ex1.insert(15);
// 	ex1.insert(15);
// 	ex1.insert(15);
// 	ex1.insert(15);
// 	ex1.insert(15);
// 	ex1.insert(15);
// 	ex1.print();

// 	PRINT << TXT_NL << "Count 15s: " << ex1.count(15) << TXT_NL << std::endl;
// 	PRINT << TXT_NL << "Count 32s: " << ex1.count(32) << TXT_NL << std::endl;

// 	PRINT << TXT_NL << "El gilipollas insert: " << TXT_NL;
// 	ex1.insert(ex1.end(), 3);
// 	ex1.insert(ex1.begin(), 50);
// 	PRINT << TXT_NL << "El de guays insert: " << TXT_NL;
// 	ex1.insert(ex1.end(), 90);
// 	ex1.insert((ex1.begin() + 2), 4);
// 	ex1.print();

// 	PRINT << std::boolalpha << "Bintree ex1 is empty: " << ex1.empty() << END;
// 	PRINT << "Bintree ex1 size: " << ex1.size() << END;

// 	PRINT 	<< TXT_NL << "Lower Bound: " << ex1.lower_bound(30)->data
// 			<< TXT_NL << "Lower Bound: " << ex1.lower_bound(43)->data
// 			<< TXT_NL << "Lower Bound: " << (ex1.lower_bound(59) == ex1.end() ? "END" : "ERROR")
// 			<< TXT_NL << "Lower Bound: " << ex1.lower_bound(1)->data 
// 			<< TXT_NL << "Lower Bound: " << ex1.lower_bound(4)->data 
// 			<< TXT_NL << "Lower Bound: " << ex1.lower_bound(16)->data
// 			<< TXT_NL << "Lower Bound: " << ex1.lower_bound(14)->data
// 			<< TXT_NL << "Lower Bound: " << ex1.lower_bound(25)->data
// 			<< END;

// 	PRINT 	<< TXT_NL << "Upper Bound: " << ex1.upper_bound(30)->data
// 			<< TXT_NL << "Upper Bound: " << ex1.upper_bound(43)->data
// 			<< TXT_NL << "Upper Bound: " << (ex1.upper_bound(59) == ex1.end() ? "END" : "ERROR")
// 			<< TXT_NL << "Upper Bound: " << ex1.upper_bound(1)->data 
// 			<< TXT_NL << "Upper Bound: " << ex1.upper_bound(4)->data 
// 			<< TXT_NL << "Upper Bound: " << ex1.upper_bound(16)->data
// 			<< TXT_NL << "Upper Bound: " << ex1.upper_bound(14)->data
// 			<< TXT_NL << "Upper Bound: " << ex1.upper_bound(25)->data
// 			<< END;

// 	ex1.insert(43);
// 	ex1.print();


// // 	/* DELETE */
// // 	PRINT	<< TXT_NL << "DELETE BY RANGE TEST" << END;
// // 	//ex1.erase(ex1.begin() + 1);
// // 	ft::bintree<int>::iterator dfirst = (ex1.begin() + 1);
// // 	ft::bintree<int>::iterator dlast = (ex1.end() - 2);
// // 	ex1.erase(dfirst, dlast);
// // 	ex1.print();
// // PRINT	<< TXT_NL << "/DELETE BY RANGE TEST" << END;
	
// 	ex2.insert(42);
// 	ex2.insert(15);
// 	ex2.insert(58);
// 	ex2.insert(2);
// 	ex2.insert(26);
// 	ex2.print();

// 	PRINT << TXT_NL << "Insert 27 " << END;

// 	ex2.insert(27);
// 	ex2.print();


// 	// ft::bintree<int>::iterator del_this(ex2.begin());
// 	// ex2.erase(del_this[3]);




// 	PRINT << "MIEDO" << END;
// 	ex2.print();



// 	test2.insert("cuarenta y dos", "CUARENTA Y DOS: \t\t\tEl significado de la vida, el universo, y todo.");
// 	test2.insert("ordenador", "ORDENADOR: \t\t\t\tDispositivo que ordena e interpreta información almacenada en una serie de dígitos binarios.");
// 	test2.insert("piscina", "PISCINA: \t\t\t\tEscabechina de aspirantes a estudiantes.");
// 	test2.insert("arbol binario de rojos y negros", "ÁRBOL BINARIO DE ROJOS Y NEGROS: \tEstructura de datos incestuosa que reduce el tiempo de búsqueda a costa de hacer de tu padre el hijo de ti y de tu abuelo.");
// 	test2.insert("tig", "TIG: \t\t\t\t\tTrabajo de interés general.");
// 	test2.insert("lista enlazada", "LISTA ENLAZADA: \t\t\tEstructura de datos en la que cada elemento enlaza el siguiente y el anterior. Lentas en comparaciones e iteraciones, pero rápidas en inserciones y borrados.");
// 	test2.insert("array", "ARRAY: \t\t\t\t\tEstructura de datos contiguos en memoria RAM. Rápidos en comparaciones e iteraciones, pero lentos en inserciones y borrados.");
// 	test2.insert("marvin", "MARVIN: \t\t\t\tRobot cascarrabias.");
// 	test2.insert("norminette", "NORMINETTE: \t\t\t\tGuía de estilo que asegura que nadie podrá entender tu código.");
// 	test2.insert("cafe", "CAFÉ: \t\t\t\t\tBien de primera necesidad para la supervivencia elaborada a partir de granos de café molidos y agua.");
// 	test2.insert("agua", "AGUA: \t\t\t\t\tBien de primera necesidad por ser necesaria para la elaboración del café (véase: cafe).");
// 	test2.insert("compilador", "COMPILADOR: \t\t\t\tÚnico profesor en activo de 42.");
	
// 	// test2.insert("cuarenta y dos", 42);
// 	// test2.insert("uno", 1);
// 	// test2.insert("noventa y nueve", 99);
// 	// test2.insert("veintisiete", 27);
// 	// test2.insert("dos", 2);
// 	// test2.insert("sesenta y ocho", 68);
// 	// test2.insert("ochenta y tres", 83);
// 	// test2.insert("treinta y cuatro", 34);
// 	// test2.print();

// 	// test2.insert(42, 42);
// 	// test2.insert(1, 1);
// 	// test2.insert(99, 99);
// 	// test2.insert(27, 27);
// 	// test2.insert(2, 2);
// 	// test2.insert(68, 68);
// 	// test2.insert(83, 83);
// 	// test2.insert(34, 34);
// 	// //test2.print();

// 	// ft::bintree<int>::iterator ex1end = ex1.end();	
// 	// (void)ex1end;

// 	PRINT << TXT_NL << "Tree size: " << ex1.size() << END;
// 	for (ft::bintree<int>::iterator it = ex1.begin(), end = ex1.end(); it != end; ++it)
// 		PRINT << it->data << END;

// 	ft::bintree<int>::iterator reftest = ex1.begin();
// 	PRINT << "REFTEST: " << reftest[2].data << END;

// 	PRINT << TXT_NL;

// 	for (ft::bintree<int>::reverse_iterator it = ex1.rbegin(), end = ex1.rend(); it != end; ++it)
// 		PRINT << it->data << END;

// 	PRINT << TXT_NL;
// 	// PRINT << "EX2 POST-DELETE" << END;

// 	// for (ft::bintree<int>::iterator it = ex2.begin(), end = ex2.end(); it != end; ++it)
// 	// 	PRINT << it->data << END;

// 	// ft::bintree<int>::iterator ex42 = *(ex1.getNode(42));
// 	// PRINT << (*ex42).data << END;
// 	// ++ex42;
// 	// if (ex42 == ex1.end())
// 	// 	PRINT << "bleh" << END;

// 	PRINT << "EL ABECEDARIO DE 42" << END;

// 	PRINT << TXT_NL << "Dictionary size: " << test2.size() << END;
	
// 	for (Dictionary::iterator it = test2.begin(), end = test2.end(); it != end; ++it)
// 		PRINT << it->data.second << END;

// 	PRINT 	<< TXT_NL << "Lower Bound 'cafeteria' : " << test2.lower_bound("cafeteria")->data.first
// 			<< TXT_NL << "Lower Bound 'marvinovich': " << test2.lower_bound("marvinovich")->data.first
// 			<< TXT_NL << "Lower Bound 'tigs': " << (test2.lower_bound("tigs") == test2.end() ? "END" : "ERROR")
// 			<< TXT_NL << "Lower Bound 'aguafiestas': " << test2.lower_bound("aguafiestas")->data.first
// 			<< TXT_NL << "Lower Bound 'agu': " << test2.lower_bound("agu")->data.first
// 			<< TXT_NL << "Lower Bound 'ordenador': " << test2.lower_bound("ordenador")->data.first
// 			<< TXT_NL << "Lower Bound: 'tif': " << test2.lower_bound("tif")->data.first
// 			<< END;

// 	PRINT 	<< TXT_NL << "Upper Bound 'cafeteria' : " << test2.upper_bound("cafeteria")->data.first
// 			<< TXT_NL << "Upper Bound 'marvinovich': " << test2.upper_bound("marvinovich")->data.first
// 			<< TXT_NL << "Upper Bound 'tigs': " << (test2.upper_bound("tigs") == test2.end() ? "END" : "ERROR")
// 			<< TXT_NL << "Upper Bound 'aguafiestas': " << test2.upper_bound("aguafiestas")->data.first
// 			<< TXT_NL << "Upper Bound 'agu': " << test2.upper_bound("agu")->data.first
// 			<< TXT_NL << "Upper Bound 'ordenador': " << test2.upper_bound("ordenador")->data.first
// 			<< TXT_NL << "Upper Bound: 'tif': " << test2.upper_bound("tif")->data.first
// 			<< END;

// 	ft::pair<Dictionary::iterator, Dictionary::iterator> ajoyagua(test2.equal_range("a"));
// 	PRINT 	<< TXT_NL << "Equal Range 'agua': " <<  ajoyagua.first->data.first << " " << ajoyagua.second->data.first
// 			<< END;

// 	PRINT	<< TXT_NL << "Print by Reference: " << TXT_NL << test2["arbol binario de rojos y negros"] << END;
// 	PRINT	<< TXT_NL << "Insert by Reference: " << TXT_NL << (test2["santana"] = "SANTANA: \t\t\t\tCanario estepario.") << END;
// 	PRINT	<< TXT_NL << "Print by Reference: " << TXT_NL << ex1[15] << END;
// 	PRINT	<< TXT_NL << "Insert by Reference: " << TXT_NL << ex1[89] << END;
// 	ex1.print();
	
// 	// PRINT << TXT_NL;
// 	// PRINT << "DELETE MARVIN'S ENTRY xD" TXT_NL;
// 	// test2.erase(test2.getNode("marvin"));
// 	// PRINT << TXT_NL;

// 	PRINT << TXT_NL << "Dictionary size: " << test2.size() << END;
// 	for (Dictionary::iterator it = test2.end() - 1, end = test2.begin() - 1; it != end; --it)
// 		PRINT << it->data.second << END;

// 	PRINT << TXT_NL;
	
// 	for (Dictionary::reverse_iterator it = test2.rbegin(), end = test2.rend(); it != end; ++it)
// 		PRINT << it->data.second << END;

// 	Dictionary	new_dictionary;

// 	 PRINT << TXT_NL << "RANGE INSERTED DICTIONARY" << TXT_NL << END;
	
// 	 new_dictionary.insert(test2.begin(), test2.end());

// 	 for (ft::bintree_pair<std::string, std::string>::iterator it = new_dictionary.begin(), end = new_dictionary.end(); it != end; ++it)
// 	 	PRINT << it->data.second << END;

// 	// PRINT << TXT_NL "BAD RANGE DELETE (SHOULD BE IGNORED)" TXT_NL << END;
// 	// test2.erase(new_dictionary.begin(), new_dictionary.end());
// 	// for (ft::bintree_pair<std::string, std::string>::iterator it = new_dictionary.begin(), end = new_dictionary.end(); it != end; ++it)
// 	// 	PRINT << it->data.second << END;

// 	// PRINT << TXT_NL "DELETE NORMINETTE'S ENTRY BY KEY " TXT_NL << END;
// 	// new_dictionary.erase("norminette");
// 	// for (ft::bintree_pair<std::string, std::string>::iterator it = new_dictionary.begin(), end = new_dictionary.end(); it != end; ++it)
// 	// {
// 	// 	if (it->next == it->_end)
// 	// 		PRINT << "I point to end! " << *it->key << END;
// 	// 	else
// 	// 		PRINT << "I point to " << *it->next->key << "!" << END;
// 	// 	PRINT << it->data.second << END;
// 	// }
// 	// size_t haalp = 0;
// 	// for (ft::bintree_pair<std::string, std::string>::iterator it = new_dictionary.begin(); haalp < 15; ++haalp, ++it)
// 	// 	std::cerr << "sollozo: " << it->key << *it->key << std::endl;

// 	PRINT << TXT_NL "SANTANA DELETE " TXT_NL << END;
// 	new_dictionary.erase("santana");
// 	for (ft::bintree_pair<std::string, std::string>::iterator it = new_dictionary.begin(), end = new_dictionary.end(); it != end; ++it)
// 	{
// 		//PRINT << "AAAAAH" << END;
// 		if (it->next == NULL)
// 			PRINT << "I point to end! " << *it->key << END;
// 		else
// 			PRINT << "I point to " << *it->next->key << "!" << END;
// 		PRINT << it->data.second << END;
// 	}

// 	for (ft::bintree_pair<std::string, std::string>::reverse_iterator rit = new_dictionary.rbegin(), rend = new_dictionary.rend(); rit != rend; ++rit)
// 	{
// 		if (rit->next == NULL)
// 			PRINT << "I point to end! " << *rit->key << END;
// 		else
// 			PRINT << "I point to " << *rit->next->key << "!" << END;
// 		PRINT << rit->data.second << END;
// 	}

// 	ft::bintree_pair<std::string, std::string>::iterator	carmensandiego = (new_dictionary.end() - 1);
// 	PRINT << "Where in the world is TIG? " << *carmensandiego->value << END;


// 	//VALE. EL PLAN. SACAR EL HILO DE LOS NODOS!!!! UN VECTOR DE ENLACES EN LA CLASE!!!!
// 	//MUAAAAAAAAAJAJAJAJAJAJAJAAJAJAJAAAAAA!!!!!!!
// 	//MAYBE THREAD SHOULD BE STD::LIST????? HMMMMMMM
// 	PRINT << TXT_NL "GOOD RANGE DELETE" TXT_NL << END;
// 	PRINT << "<EL GRAN PLAN>" << END;
// 	PRINT << "DELETE FROM BEGIN TO END - 2" << TXT_NL << END;
// 	new_dictionary.erase(new_dictionary.begin(), new_dictionary.end() - 2);
// 	for (ft::bintree_pair<std::string, std::string>::iterator it = new_dictionary.begin(), end = new_dictionary.end(); it != end; ++it)
// 		PRINT << it->data.second << END;
// 	PRINT << "New size: " << new_dictionary.size() << END;
// 	PRINT << "</EL GRAN PLAN>" << TXT_NL << END;

// 	PRINT << "SWAP TEST" << TXT_NL << END;
// 	ft::swap(test2, new_dictionary);
// 	PRINT << "TEST2" << END;
// 	for (ft::bintree_pair<std::string, std::string>::iterator it = test2.begin(), end = test2.end(); it != end; ++it)
// 		PRINT << it->data.second << END;
// 	PRINT << TXT_NL << "NEW_DICTIONARY" << END;
// 	for (ft::bintree_pair<std::string, std::string>::iterator it = new_dictionary.begin(), end = new_dictionary.end(); it != end; ++it)
// 		PRINT << it->data.second << END;
// 	PRINT << END;

// 	ft::map<std::string, std::string> default_constructed_map;

// 	std::map<std::string, std::string>	comp_dict;
// 	comp_dict.insert(std::make_pair("cuarenta y dos", "CUARENTA Y DOS: \t\t\tEl significado de la vida, el universo, y todo."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("ordenador", "ORDENADOR: \t\t\t\tDispositivo que ordena e interpreta información almacenada en una serie de dígitos binarios."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("piscina", "PISCINA: \t\t\t\tEscabechina de aspirantes a estudiantes."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("arbol binario de rojos y negros", "ÁRBOL BINARIO DE ROJOS Y NEGROS: \tEstructura de datos incestuosa que reduce el tiempo de búsqueda a costa de hacer de tu padre el hijo de ti y de tu abuelo."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("tig", "TIG: \t\t\t\t\tTrabajo de interés general."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("lista enlazada", "LISTA ENLAZADA: \t\t\tEstructura de datos en la que cada elemento enlaza el siguiente y el anterior. Lentas en comparaciones e iteraciones, pero rápidas en inserciones y borrados."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("array", "ARRAY: \t\t\t\t\tEstructura de datos contiguos en memoria RAM. Rápidos en comparaciones e iteraciones, pero lentos en inserciones y borrados."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("marvin", "MARVIN: \t\t\t\tRobot cascarrabias."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("norminette", "NORMINETTE: \t\t\t\tGuía de estilo que asegura que nadie podrá entender tu código."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("cafe", "CAFÉ: \t\t\t\t\tBien de primera necesidad para la supervivencia elaborada a partir de granos de café molidos y agua."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("agua", "AGUA: \t\t\t\t\tBien de primera necesidad por ser necesaria para la elaboración del café (véase: cafe)."));
// 	comp_dict.insert(std::make_pair<std::string, std::string>("compilador", "COMPILADOR: \t\t\t\tÚnico profesor en activo de 42."));

// 	std::map<std::string, std::string>::iterator compit = comp_dict.begin();
// 	std::map<std::string, std::string>::iterator compend = comp_dict.end();
// 	--compend;
// 	--compend;
// 	// HASTA ESTO FUNCIONA EN MAC, POR LOS GNOMOS MÁGICOS O_O
// 	// for ( ; compit != compend; ++compit)
// 	// 	comp_dict.erase(compit);
// 	for ( ; compit != compend; )
// 		comp_dict.erase(compit++);
// 	for (compit = comp_dict.begin(), compend = comp_dict.end(); compit != compend; ++compit)
// 		std::cout << compit->second << std::endl;
	

// 	std::map<std::string, std::string>	eqtest1;
// 	std::map<std::string, std::string>	eqtest2;

// 	eqtest1.insert(std::make_pair("1", "1"));
// 	eqtest1.insert(std::make_pair("2", "2"));
// 	eqtest2.insert(std::make_pair("0", "1"));
// 	eqtest2.insert(std::make_pair("1", "2"));

// 	PRINT << "Equal is key ?: " << TXT_NL << (eqtest1.begin() == eqtest2.begin()) << END;
// 	PRINT << "Equal is address ?: " << (eqtest1.begin() == eqtest1.begin()) << END;
// 	PRINT << "Ends are NULL ?: " << (eqtest1.end() == eqtest2.end()) << END;
// 	//PRINT << "End == Begin - 1 ?: " << ((--eqtest1.begin()) == eqtest2.end()) << END;

// 	PRINT << "MAP TIENE DOS COMPORTAMIENTOS DISTINTOS PARA END Y --BEGIN O_O" << END;


// 	// Implementación LINUX, piensa como yo! Implementación MAC, no piensa como yo.
// 	// PARA VARIAR!!! xD En MAC esto tira segfault, en Linux bucle infinito.
// 	// size_t i = 0;
// 	// for(std::map<std::string, std::string>::iterator it = eqtest1.begin(); i < 8; ++it, ++i)
// 	// 	{PRINT << "Iteration test STL: " << &(*it) << END;}

// 	// PRINT << "QUÉ LÍO" << END;
// 	// i = 0;
// 	// for(std::map<std::string, std::string>::iterator it = (--eqtest1.end()); i < 8; --it, ++i)
// 	// 	{PRINT << "Iteration test STL: " << &(*it) << END;}
// 	// PRINT << "QUÉ LÍO NO BAJA DE REND/BEGIN!? !? WHYYYYYY" << END;
// 	// i = 0;
// 	// for(std::map<std::string, std::string>::reverse_iterator rit = eqtest1.rbegin(); i < 8; ++rit, ++i)
// 	// 	{PRINT << (i == 2 ? "REND" : "Iteration test STL: ") << &(*rit) << END;}
	
// 	std::cout << "piim" << std::endl;
// 	// PRINT << "QUÉ LÍO" << END;
// 	// i = 0;
// 	// for(std::map<std::string, std::string>::reverse_iterator rit = (++eqtest1.rend()); i < 8; --rit, ++i)
// 	// 	{PRINT << "Iteration test STL: " << &(*rit) << END;}

// 	// if (iterator_tests())
// 	// 	PRINT << TXT_BGRN "OK" << END;
// 	// else
// 	// 	PRINT << TXT_BRED "KO" << END;
// 	// if (my_veritable_vector<ft::vector<int>, std::vector<int> >())
// 	// 	PRINT << TXT_BGRN "OK" << END;
// 	// else
// 	// 	PRINT << TXT_BRED "KO" << END;

// 	//quick make_pair test
// 	// using ft::make_pair;
// 	// ft::pair<int, char> pair_chorra = make_pair(42, 42);
// 	// std::pair<int, char> std_pair_chorra = std::make_pair(42, 42);
// 	// std::cout << "STD PAIR CHORRA: " << std_pair_chorra.first << " " << std_pair_chorra.second << std::endl;
// 	// std::cout << "FT PAIR CHORRA: " << pair_chorra.first << " " << pair_chorra.second << std::endl;
// 	// ft::pair<int, char>	pair_chorra(42, 42);
// 	// std::pair<int, char> std_pair_chorra(42, 42);

// 	// PRINT << TXT_BYEL "MY PAIR_CHORRA: " TXT_BGRN << pair_chorra.first << TXT_BYEL ", " TXT_BGRN << pair_chorra.second << END;
// 	// PRINT << TXT_BYEL "STD PAIR_CHORRA: " TXT_BGRN << std_pair_chorra.first << TXT_BYEL ", " TXT_BGRN << std_pair_chorra.second << END;

// 	// //enable_if test
// 	// //Change to non-integral (double, float, etc.) to test. :)
// 	// PRINT << TXT_BYEL "ENABLE_IF TEST:" << TXT_NL;
// 	// int	i = 1;
// 	// PRINT << TXT_TAB << ALN << "i is odd: " << std::boolalpha << TXT_BGRN << ft::is_odd(i) << END;

// 	// std::string	test1 = "Apple";
// 	// std::string test2 = "honey";
// 	// std::string test3 = "honey";
// 	// bool std_ret;

// 	// std_ret = std::lexicographical_compare<std::string::iterator, std::string::iterator>(test1.begin(), test1.end(), test2.begin(), test2.end());

// 	// PRINT << TXT_BGRN << std::boolalpha << std_ret << END;

// 	// std_ret = ft::lexicographical_compare<std::string::iterator, std::string::iterator>(test1.begin(), test1.end(), test2.begin(), test2.end());
// 	// PRINT << TXT_BGRN << std::boolalpha << std_ret << END;

// 	// std_ret = ft::equal<std::string::iterator, std::string::iterator>(test2.begin(), test2.end(), test3.begin());
// 	// PRINT << TXT_BGRN << std::boolalpha << std_ret << END;

// 	// std_ret = ft::equal<std::string::iterator, std::string::iterator>(test2.begin(), test2.end(), test1.begin());
// 	// PRINT << TXT_BGRN << std::boolalpha << std_ret << END;
// 	// // //DEBUG
// 	// // {
// 	// // 	PRINT << TXT_BYEL << "THE GREAT IS_INTEGRAL TEST!" << TXT_NL
// 	// // 	<< "Double Is Integral?" << std::boolalpha << " " << std::is_integral<double>::value << TXT_NL
// 	// // 	<< "Float Is Integral?" << std::boolalpha << " " << std::is_integral<float>::value << TXT_NL
// 	// // 	<< "Unsigned Int Is Integral?" << std::boolalpha << " " << std::is_integral<unsigned int>::value << END;
// 	// // }
// 	// // //DEBUG

	return (0);
}