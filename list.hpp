#pragma once
namespace cosmos
{
	template <class... T>
	struct list
	{
	};

	namespace detail 
	{
		template<typename List, typename... T>
		struct push_back_detail;

		template<template<class...> class List, class... Elements, class... T>
		struct push_back_detail<List<Elements...>, T...> {
			using type = List<Elements..., T...>;
		};

		template<typename List, typename... T>
		struct push_front_detail;

		template<template<class...> class List, class... Elements, class... T>
		struct push_front_detail<List<Elements...>, T...>
		{
			using type = List<T..., Elements...>;
		};

		template<typename List>
		struct pop_front_detail;

		template<template<class...> class List, class Head, class... Tail>
		struct pop_front_detail<List<Head, Tail...>>
		{
			using type = List<Tail...>;
		};

		template<template<class...> class List>
		struct pop_front_detail<List<>>
		{
			using type = List<>;
		};

		template<typename List>
		struct front_detail;

		template<template<class...> class List, class Head, class... Tail>
		struct front_detail<List<Head, Tail...>>
		{
			using type = Head;
		};

		template<template<class...> class List>
		struct front_detail<List<>>
		{
			using type = List<>;
		};

		template<size_t Index, class List>
		struct at_detail;

		template<size_t Index, template<class...> class List, class T, class... Rest>
		struct at_detail<Index, List<T, Rest...>> {
			using type = typename at_detail<Index - 1, List<Rest...>>::type;
		};

		template<template<class...> class List, class T, class... Rest>
		struct at_detail<0, List<T, Rest...>> {
			using type = T;
		};
	}

	template<typename List, typename... T>
	using push_back = typename detail::push_back_detail<List, T...>::type;

	template<typename List, typename... T>
	using push_front = typename detail::push_front_detail<List, T...>::type;

	template<typename List>
	using pop_front = typename detail::pop_front_detail<List>::type;

	template<typename List>
	using front = typename detail::front_detail<List>::type;

	template<class List> struct size;

	template<template<class...> class List, class... Elements>
	struct size<List<Elements...>> : std::integral_constant<std::size_t, sizeof...(Elements)> {};

	template<size_t Index, class List>
	using at = typename detail::at_detail<Index, List>::type;

	template<class List>
	using back = typename detail::at_detail<size<List>::value-1, List>::type;

	namespace detail
	{
		template<size_t Index, class List>
		struct erase_at_detail;

		template<size_t Index, template<class...> class List, class T, class... Rest>
		struct erase_at_detail<Index, List<T, Rest...>> {
			using type = cosmos::push_front<typename erase_at_detail <Index - 1, List<Rest...>>::type, T>;
		};

		template<template<class...> class List, class T, class... Rest>
		struct erase_at_detail<0, List<T, Rest...>> {
			using type = List<Rest...>;
		};

		template<size_t Index, class T, class R>
		struct split_detail{
			using head = push_back<T, front<R>>;
			using tail = pop_front<R>;
			using type = typename split_detail<Index - 1, head, tail>::type;
		};

		template<class T, class R>
		struct split_detail<0, T, R> {
			using type = T;
		};

		///
		template<size_t Index, class List>
		struct split_detail1;

		template<size_t Index, template<class...> class List, class T, class... Rest>
		struct split_detail1<Index, List<T, Rest...>> {
			using type = push_front<typename split_detail1<Index-1, List<Rest...>>::type, T>;
		};

		template<template<class...> class List, class T, class... Rest>
		struct split_detail1<0, List<T, Rest...>> {
			using type = List<>;
		};

		template<class List1, class List2>
		struct append_detail;

		template<template<class...> class L1, class... T1, template<class...> class L2, class... T2>
		struct append_detail<L1<T1...>, L2<T2...>> {
			using type = L1<T1..., T2...>;
		};

		///
		template<class List>
		struct reverse_detail;

		template<template<class...> class List, class T, class... Rest>
		struct reverse_detail<List<T, Rest...>> {
			using type = push_back<typename reverse_detail<List<Rest...>>::type, T>;
		};

		template<template<class...> class List>
		struct reverse_detail<List<>> {
			using type = List<>;
		};

		template<class List1, template<class...> class List2>
		struct rename_detail;

		template<template<class...> class L1, class... T1, template<class...> class L2>
		struct rename_detail<L1<T1...>, L2> {
			using type = L2<T1...>;
		};

		template<size_t Index, class U, class List>
		struct index_of_impl;

		template<size_t Index, class U, template<class...> class List, class T, class... Rest>
		struct index_of_impl<Index, U, List<T, Rest...>> {
			using type = typename index_of_impl<Index + 1, U, List<Rest...>>::type;
		};

		template<size_t Index, template<class...> class List, class T, class... Rest>
		struct index_of_impl<Index, T, List<T, Rest...>> {
			using type = std::integral_constant<int, Index>;
		};

		template<size_t Index, class T, template<class...> class List>
		struct index_of_impl<Index, T, List<>> {
			using type = std::integral_constant<int, -1>;
		};

		template<class U, class List>
		struct erase_type_impl;

		template<class U, template<class...> class List, class T, class... Rest>
		struct erase_type_impl<U, List<T, Rest...>> {
			using type = push_front<typename erase_type_impl<U, List<Rest...>>::type, T>;
		};

		template<template<class...> class List, class T, class... Rest>
		struct erase_type_impl<T, List<T, Rest...>> {
			using type = List<Rest...>;
		};

		template<class T, template<class...> class List>
		struct erase_type_impl<T, List<>> {
			using type = List<>;
		};

		template<class U, class List>
		struct erase_type_all_impl;

		template<class U, template<class...> class List, class T, class... Rest>
		struct erase_type_all_impl<U, List<T, Rest...>> {
			using type = push_front<typename erase_type_all_impl<U, List<Rest...>>::type, T>;
		};

		template<template<class...> class List, class T, class... Rest>
		struct erase_type_all_impl<T, List<T, Rest...>> {
			using type = typename erase_type_all_impl<T, List<Rest...>>::type;
		};

		template<class T, template<class...> class List>
		struct erase_type_all_impl<T, List<>> {
			using type = List<>;
		};

		template<class List>
		struct erase_dupl_impl;

		template<template<class...> class List, class T, class... Rest>
		struct erase_dupl_impl<List<T, Rest...>> {
			using rest = typename erase_dupl_impl<List<Rest...>>::type;
			using erase_list = typename erase_type_all_impl<T, rest>::type;

			using type = push_front<erase_list, T>;
			using type1 = push_front<typename erase_type_all_impl<T, typename erase_dupl_impl<List<Rest...>>::type>::type, T>;
		};

		template<template<class...> class List>
		struct erase_dupl_impl<List<>> {
			using type = List<>;
		};

		template<typename R, typename T, typename List> //R is a repalce type, T is destination in List
		struct replace_all_impl;

		template<typename R, typename T, template<class...> class List, class H, class... Elements>
		struct replace_all_impl<R, T, List<H, Elements...>>{
			using type = push_front<typename replace_all_impl<R, T, List<Elements...>>::type, H>;
		};

		template<typename R, typename T, template<class...> class List, class... Rest>
		struct replace_all_impl<R, T, List<T, Rest...>> {
			using type = push_front<typename replace_all_impl<R, T, List<Rest...>>::type, R>;
		};

		template<typename R, typename T, template<class...> class List>
		struct replace_all_impl<R, T, List<>> {
			using type = List<>;
		};

		template<size_t Index, class T, class List>
		struct replace_at_detail;

		template<size_t Index, class U, template<class...> class List, class T, class... Rest>
		struct replace_at_detail<Index, U, List<T, Rest...>> {
			using type = push_front<typename replace_at_detail<Index - 1, U, List<Rest...>>::type, T>;
		};

		template<class U, template<class...> class List, class T, class... Rest>
		struct replace_at_detail<0, U, List<T, Rest...>> {
			using type = List<U, Rest...>;
		};

		template<size_t Index, class List>
		struct erase_front_impl;

		template<size_t Index, template<class...> class List, class T, class... Rest>
		struct erase_front_impl<Index, List<T, Rest...>> {
			using type = typename erase_front_impl<Index - 1, List<Rest...>>::type;
		};

		template<template<class...> class List, class T, class... Rest>
		struct erase_front_impl<0, List<T, Rest...>>
		{
			using type = List<T, Rest...>;
		};

		template<template<class...> class F, typename L>
		struct transform_impl;

		template<template<class...> class F, template<class...> class L>
		struct transform_impl<F, L<>> {
			using type = L<>;
		};

		template<template<class...> class F, template<class...> class L, class T, class... Rest>
		struct transform_impl<F, L<T, Rest...>> {
			//using _first = F<T>;
			//using _rest = typename transform_impl<F, L<Rest...>>::type;

			//using type = push_front<_rest, _first>;

			using type = push_front<typename transform_impl<F, L<Rest...>>::type, F<T>>;
		};

		template<template<class...> class F, typename L>
		struct transform_impl1;

		template<template<class...> class F, template<class...> class L, class... T>
		struct transform_impl1<F, L<T...>> {
			using type = L<F<T>...>;
		};
	}

	template<size_t Index, class List>
	using erase_at = typename detail::erase_at_detail<Index, List>::type;

	template<size_t Index, class List>
	using split1 = typename detail::split_detail1<Index, List>::type;

	template<size_t Index, class List, class K=list<> >
	using split = typename detail::split_detail<Index, K, List>::type;

	template<class List>
	using pop_back = split1<size<List>::value - 1, List>;

	template<class List1, class List2>
	using append = typename detail::append_detail<List1, List2>::type;

	template<class List>
	using as_tuple = typename detail::rename_detail<List, std::tuple>::type;

	template<class List>
	using as_pair = typename detail::rename_detail<List, std::pair>::type;

	//template<class List1, class List2>
	//using as_variant = typename detail::rename_detail<List1, std::variant>::type;

	template<class List>
	using reverse = typename detail::reverse_detail<List>::type;

	template<class T, class List>
	using index_of = typename detail::index_of_impl<0, T, List>::type;

	template<class T, class List>
	using erase_type = typename detail::erase_type_impl<T, List>::type;

	template<class T, class List>
	using erase_all = typename detail::erase_type_all_impl<T, List>::type;

	template<class List>
	using erase_dupl = typename detail::erase_dupl_impl<List>::type;

	template<typename R, typename T, typename List>
	using replace_all = typename detail::replace_all_impl<R, T, List>::type;

	template<size_t Index, class T, class List>
	using replace_at = typename detail::replace_at_detail<Index, T, List>::type;

	template<size_t Index, class List>
	using erase_front = typename detail::erase_front_impl<Index, List>::type;

	template<size_t Start, size_t End, class List>
	struct slice_impl {
		using type = erase_front<Start, split1<End, List>>;
	};

	template<size_t Start, size_t End, class List>
	using slice = typename slice_impl<Start, End, List>::type;

	template<template<class...> class F, typename L>
	using transform = typename detail::transform_impl1<F, L>::type;
}