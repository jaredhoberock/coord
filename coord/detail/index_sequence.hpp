#pragma once

#include "prologue.hpp"


COORD_NAMESPACE_OPEN_BRACE


namespace detail
{


template<size_t... I> struct index_sequence {};

template<size_t Start, typename Indices, size_t End>
struct make_index_sequence_impl;

template<size_t Start, size_t... Indices, size_t End>
struct make_index_sequence_impl<
  Start,
  index_sequence<Indices...>, 
  End
>
{
  typedef typename make_index_sequence_impl<
    Start + 1,
    index_sequence<Indices..., Start>,
    End
  >::type type;
};

template<size_t End, size_t... Indices>
struct make_index_sequence_impl<End, index_sequence<Indices...>, End>
{
  typedef index_sequence<Indices...> type;
};

template<size_t N>
using make_index_sequence = typename make_index_sequence_impl<0, index_sequence<>, N>::type;


} // end detail


COORD_NAMESPACE_CLOSE_BRACE

#include "epilogue.hpp"

