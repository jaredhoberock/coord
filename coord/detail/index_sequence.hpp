#pragma once

#include "prologue.hpp"

#include <cstdint>


COORD_NAMESPACE_OPEN_BRACE


namespace detail
{


template<std::size_t... I> struct index_sequence {};

template<std::size_t Start, typename Indices, std::size_t End>
struct make_index_sequence_impl;

template<std::size_t Start, std::size_t... Indices, std::size_t End>
struct make_index_sequence_impl<
  Start,
  index_sequence<Indices...>, 
  End
>
{
  using type = typename make_index_sequence_impl<
    Start + 1,
    index_sequence<Indices..., Start>,
    End
  >::type;
};

template<std::size_t End, std::size_t... Indices>
struct make_index_sequence_impl<End, index_sequence<Indices...>, End>
{
  using type = index_sequence<Indices...>;
};

template<std::size_t N>
using make_index_sequence = typename make_index_sequence_impl<0, index_sequence<>, N>::type;


template<class Indices>
struct make_reversed_index_sequence_impl;

template<std::size_t... Indices>
struct make_reversed_index_sequence_impl<index_sequence<Indices...>>
{
  using type = index_sequence<(sizeof...(Indices) - 1 - Indices)...>;
};


template<std::size_t N>
using make_reversed_index_sequence = typename make_reversed_index_sequence_impl<make_index_sequence<N>>::type;


} // end detail


COORD_NAMESPACE_CLOSE_BRACE

#include "epilogue.hpp"

