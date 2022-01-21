/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 18:49:21 by miki              #+#    #+#             */
/*   Updated: 2022/01/21 05:00:29 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../testers.hpp"

#ifdef __MACH__
# include <sys/time.h>
# include <mach/mach_time.h>
# include <mach/clock.h>
# include <mach/mach.h> //check without this
#elif __linux__
# include <time.h>
#endif

#define PRINT std::cout
#define ALN std::left << std::setw(30)
#define END TXT_RST << std::endl
#define SET std::setw(9) << color

/*
** These are the definitions for the execution timer functions with nanosecond
** resolution. On Intel Macs, system ticks are defined to equal one nanosecond,
** and mach_absolute_time, defined in Apple libraries, renders number of ticks
** since epoch, so on the 42 school Macs I use that.
**
** On my home Linux machine this functionality is provided by clock_gettime,
** which returns nanoseconds since epoch in timespec format (seconds and
** nanoseconds), which are then converted to raw nanoseconds.
**
** The timers are used to clock execution time for certain container
** functionalities, such as insert, find, access or erase.
*/
#ifdef __MACH__
void	start_timer(__uint64_t * start)
{
	*start = mach_absolute_time();
}

__int64_t	stop_timer_nanosec(__uint64_t * start)
{
	__uint64_t end;
	end = mach_absolute_time();
	return (end - *start);
}
#elif __linux__
void	start_timer(__uint64_t * start)
{
	struct timespec	time;
	clock_gettime(CLOCK_MONOTONIC, &time);
	*start = time.tv_sec * 1000000000 + time.tv_nsec;
}

__int64_t	stop_timer_nanosec(__uint64_t * start)
{
	struct timespec	ts_end;
	clock_gettime(CLOCK_MONOTONIC, &ts_end);
	__uint64_t		end = ts_end.tv_sec * 1000000000 + ts_end.tv_nsec;
	return (end - *start);
}
#endif

/*
** I ended up doing this test a lot in certain parts of my map tester.
*/
bool	isGreen(std::string const color) {
	return (color.compare(TXT_BGRN) == 0);
}

/*
** This function checks FT execution time against STL execution time. If the
** difference is greater than 20 times the STL execution time, we consider it
** an error. Otherwise, we consider the test successful. This test isn't called
** for ALL container functions, just the obvious ones, insert,
** insert with hint, erase, access, etc. We don't call it for stuff like size,
** for example.
**
** IMPORTANT NOTE:
** Though the time value I use is in nanoseconds, in practice on the school Macs
** the monoclock seems to only have a resolution in the MICROSECONDS. It changes
** in 1000 nanosecond increments. Sometimes the CPU is so fast that this
** resolution is not enough and the clock reports 0 seconds of execution time.
** This actually happens reliably in the swap test. In such cases we round up to
** the nearest MICROSECOND and report 1 microsecond of execution time.
*/
void	check_exec_time(__int64_t & ft_time, __int64_t & stl_time, bool & ret)
{
	char const *	color;
	if (stl_time == 0)
		stl_time += 1; //Round to nearest microsecond
	if (ft_time == 0)
		ft_time += 1; //Round to the nearest microsecond
	if (ft_time > stl_time * 20)
	{
		color = TXT_BRED;
		ret = false;
	}
	else if (stl_time > ft_time * 20)
		color = TXT_BCYN;
	else
		color = TXT_BGRN;
	PRINT	<< TXT_TAB << TXT_BYEL << "STL Time" << TXT_TAB << "My Time"
			<< TXT_NL << TXT_TAB << color << stl_time << TXT_TAB TXT_TAB << ft_time << END;
	ft_time = -1;
	stl_time = -1;
}
									//reference to pointer
void	check(bool result, char const *& color, bool & ret)
{
	//Return check
	if (result == true)
		color = TXT_BGRN;
	else
	{
		color = TXT_BRED;
		ret = false;
	}
}


/*
** This function will take the result of any comparison as comp. If the result
** is true, the color is set to green. If it is false, the color is set to red
** and the global return value is set to false.
**
** The message passed as a parameter will be printed to in a left and right
** column in yellow with the prefix "MY " and "STD ", respectively. The
** msg_offset will be set to the width of the longest message (std_msg). You can
** optionally specify the column width as the last argument, otherwise they
** will be separated only by a TXT_TAB.
**
** The color will be set to green or red before the function exits. It will need
** to be reset by the caller, either with TXT_RST or END!
*/
void	compare_log(bool comp, bool & ret, std::string const & msg, size_t & msg_offset, size_t const & minw)
{
	char const *		color;
	std::string	const	my_msg = "MY " + msg;
	std::string	const	std_msg = "STD " + msg;

	if (comp)
		color = TXT_BGRN;
	else
	{
		color = TXT_BRED;
		ret = false;
	}
	msg_offset = std_msg.size();
	PRINT	<< TXT_TAB << TXT_BYEL << std::setw(minw) << my_msg << TXT_TAB << std::setw(minw) << std_msg << TXT_NL
			<< TXT_TAB << color;
}
