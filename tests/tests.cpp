#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "whirl.hpp"
#include "sequential.hpp"


namespace whirl
{

////////////////////////////////////////////////////////////////////////////////////////////////////
// testing utilities
////////////////////////////////////////////////////////////////////////////////////////////////////

    struct bound_predicate_dummy
    {
        bool is(const std::istream&);
    };

    template <typename T>
    struct input_stream_dummy
    {
        constexpr input_stream_dummy(typename std::char_traits<T>::int_type tok)
            : tok{ tok }
        { }

        constexpr auto peek() noexcept
        {
            return tok;
        }

        constexpr auto get() noexcept
        {
            return tok;
        }

        constexpr void ignore() noexcept
        {
        }

        typename std::char_traits<T>::int_type tok;

    };

    template <typename T>
    struct input_source_traits<input_stream_dummy<T>>
    {
        using char_type = T;

        static char_type look_ahead(input_stream_dummy<T>& ins) noexcept
        {
            return ins.peek();
        }

        static constexpr char_type read(input_stream_dummy<T>& ins) noexcept
        {
            return ins.get();
        }

        static constexpr void ignore(input_stream_dummy<T>& ins) noexcept
        {
            ins.ignore();
        }

        static constexpr bool is_end(input_stream_dummy<T>& ins) noexcept
        {
            return ins.peek() == std::char_traits<T>::eof();
        }
    };

    using bound_predicate_conjunction_dummy_t =
        bound_predicate_conjunction<bound_predicate_dummy, bound_predicate_dummy>;

    using bound_predicate_disjunction_dummy_t =
        bound_predicate_disjunction<bound_predicate_dummy, bound_predicate_dummy>;

    using bound_predicate_negation_dummy_t = bound_predicate_negation<bound_predicate_dummy>;


    struct not_a_character {};

    template <typename I, typename R>
    R dummy_transformator(I);


////////////////////////////////////////////////////////////////////////////////////////////////////
// compile-time checks
////////////////////////////////////////////////////////////////////////////////////////////////////

    static_assert(is_character_type<char>::value);
    static_assert(is_character_type<wchar_t>::value);
    static_assert(is_character_type<char16_t>::value);
    static_assert(is_character_type<char32_t>::value);

    static_assert(are_character_types<char, wchar_t, char16_t, char32_t>::value);

    static_assert(equality_comparable<int, int>::value);

    static_assert(is_compatible_character_type<char, char>::value);
    static_assert(is_compatible_character_type<wchar_t, wchar_t>::value);
    static_assert(is_compatible_character_type<char16_t, char16_t>::value);
    static_assert(is_compatible_character_type<char32_t, char32_t>::value);

    static_assert(is_character_type_v<char>);
    static_assert(is_character_type_v<wchar_t>);
    static_assert(is_character_type_v<char16_t>);
    static_assert(is_character_type_v<char32_t>);

    static_assert(are_character_types_v<char, wchar_t, char16_t, char32_t>);

    static_assert(is_compatible_character_type_v<char, char>);
    static_assert(is_compatible_character_type_v<wchar_t, wchar_t>);
    static_assert(is_compatible_character_type_v<char16_t, char16_t>);
    static_assert(is_compatible_character_type_v<char32_t, char32_t>);

    static_assert(is_input_source_type<std::basic_istream<char>>::value);
    static_assert(is_input_source_type<std::basic_istream<wchar_t>>::value);

    static_assert(is_input_source_type_v<std::basic_istream<char>>);
    static_assert(is_input_source_type_v<std::basic_istream<wchar_t>>);

    static_assert(is_compatible_input_source_type<std::basic_istream<char>, char>::value);
    static_assert(is_compatible_input_source_type<std::basic_istream<wchar_t>, wchar_t>::value);

    static_assert(is_compatible_input_source_type_v<std::istream, char>);
    static_assert(is_compatible_input_source_type_v<std::wistream, wchar_t>);

    static_assert(is_bound_predicate<bound_predicate_dummy>::value);
    static_assert(is_bound_predicate_v<bound_predicate_dummy>);

    static_assert(is_bound_predicate_v<bound_is_predicate<char>>);
    static_assert(is_bound_predicate_v<bound_is_predicate<wchar_t>>);
    static_assert(is_bound_predicate_v<bound_is_predicate<char16_t>>);
    static_assert(is_bound_predicate_v<bound_is_predicate<char32_t>>);

    static_assert(is_bound_predicate_v<bound_is_not_predicate<char>>);
    static_assert(is_bound_predicate_v<bound_is_not_predicate<wchar_t>>);
    static_assert(is_bound_predicate_v<bound_is_not_predicate<char16_t>>);
    static_assert(is_bound_predicate_v<bound_is_not_predicate<char32_t>>);

    static_assert(is_bound_predicate_v<bound_is_one_of_predicate<char>>);
    static_assert(is_bound_predicate_v<bound_is_one_of_predicate<char, char>>);
    static_assert(is_bound_predicate_v<bound_is_one_of_predicate<char, char, char>>);
    static_assert(is_bound_predicate_v<bound_is_one_of_predicate<wchar_t>>);
    static_assert(is_bound_predicate_v<bound_is_one_of_predicate<wchar_t, wchar_t>>);
    static_assert(is_bound_predicate_v<bound_is_one_of_predicate<wchar_t, wchar_t, wchar_t>>);
    static_assert(is_bound_predicate_v<bound_is_one_of_predicate<char16_t>>);
    static_assert(is_bound_predicate_v<bound_is_one_of_predicate<char16_t, char16_t>>);
    static_assert(is_bound_predicate_v<bound_is_one_of_predicate<char16_t, char16_t, char16_t>>);
    static_assert(is_bound_predicate_v<bound_is_one_of_predicate<char32_t>>);
    static_assert(is_bound_predicate_v<bound_is_one_of_predicate<char32_t, char32_t>>);
    static_assert(is_bound_predicate_v<bound_is_one_of_predicate<char32_t, char32_t, char32_t>>);
    static_assert(is_bound_predicate_v<bound_is_one_of_predicate<char, wchar_t, char16_t>>);

    static_assert(is_bound_predicate_v<bound_is_none_of_predicate<char>>);
    static_assert(is_bound_predicate_v<bound_is_none_of_predicate<char, char>>);
    static_assert(is_bound_predicate_v<bound_is_none_of_predicate<char, char, char>>);
    static_assert(is_bound_predicate_v<bound_is_none_of_predicate<wchar_t>>);
    static_assert(is_bound_predicate_v<bound_is_none_of_predicate<wchar_t, wchar_t>>);
    static_assert(is_bound_predicate_v<bound_is_none_of_predicate<wchar_t, wchar_t, wchar_t>>);
    static_assert(is_bound_predicate_v<bound_is_none_of_predicate<char16_t>>);
    static_assert(is_bound_predicate_v<bound_is_none_of_predicate<char16_t, char16_t>>);
    static_assert(is_bound_predicate_v<bound_is_none_of_predicate<char16_t, char16_t, char16_t>>);
    static_assert(is_bound_predicate_v<bound_is_none_of_predicate<char32_t>>);
    static_assert(is_bound_predicate_v<bound_is_none_of_predicate<char32_t, char32_t>>);
    static_assert(is_bound_predicate_v<bound_is_none_of_predicate<char32_t, char32_t, char32_t>>);
    static_assert(is_bound_predicate_v<bound_is_none_of_predicate<char, wchar_t, char16_t>>);

    static_assert(is_bound_predicate_v<bound_is_end_predicate>);
    static_assert(is_bound_predicate_v<bound_is_character_predicate>);

    static_assert(is_bound_predicate_v<bound_predicate_conjunction_dummy_t>);
    static_assert(is_bound_predicate_v<bound_predicate_disjunction_dummy_t>);
    static_assert(is_bound_predicate_v<bound_predicate_negation_dummy_t>);

    // transformator type trait tests

    static_assert(is_transformator<decltype(dummy_transformator<char, int>)>::value);
    static_assert(is_transformator<decltype(dummy_transformator<wchar_t, int>)>::value);
    static_assert(is_transformator<decltype(dummy_transformator<char16_t, int>)>::value);
    static_assert(is_transformator<decltype(dummy_transformator<char32_t, int>)>::value);

    static_assert(!is_transformator<decltype(dummy_transformator<not_a_character, int>)>::value);
    static_assert(!is_transformator<decltype(dummy_transformator<int, void>)>::value);

    static_assert(is_transformator_v<decltype(dummy_transformator<char, int>)>);
    static_assert(is_transformator_v<decltype(dummy_transformator<wchar_t, int>)>);
    static_assert(is_transformator_v<decltype(dummy_transformator<char16_t, int>)>);
    static_assert(is_transformator_v<decltype(dummy_transformator<char32_t, int>)>);

    static_assert(!is_transformator_v<decltype(dummy_transformator<not_a_character, int>)>);
    static_assert(!is_transformator_v<decltype(dummy_transformator<int, void>)>);


////////////////////////////////////////////////////////////////////////////////////////////////////
// run-time checks
////////////////////////////////////////////////////////////////////////////////////////////////////

    TEST_CASE( "testing is function overloads", "[is]" )
    {
        SECTION("char tests")
        {
            input_stream_dummy<char> ins('a');
            input_stream_dummy<char> ins_eof(std::char_traits<char>::eof());

            REQUIRE((is('a').is(ins    )) == true );
            REQUIRE((is('b').is(ins    )) == false);
            REQUIRE((is('a').is(ins_eof)) == false);
        }

        SECTION("wchar_t tests")
        {
            input_stream_dummy<wchar_t> ins(L'a');
            input_stream_dummy<wchar_t> ins_eof(std::char_traits<wchar_t>::eof());

            REQUIRE((is(L'a').is(ins    )) == true );
            REQUIRE((is(L'b').is(ins    )) == false);
            REQUIRE((is(L'a').is(ins_eof)) == false);
        }

        SECTION("char16_t tests")
        {
            input_stream_dummy<char16_t> ins(u'a');
            input_stream_dummy<char16_t> ins_eof(std::char_traits<char16_t>::eof());

            REQUIRE((is(u'a').is(ins    )) == true );
            REQUIRE((is(u'b').is(ins    )) == false);
            REQUIRE((is(u'a').is(ins_eof)) == false);
        }

        SECTION("char32_t tests")
        {
            input_stream_dummy<char32_t> ins(U'a');
            input_stream_dummy<char32_t> ins_eof(std::char_traits<char32_t>::eof());

            REQUIRE((is(U'a').is(ins    )) == true );
            REQUIRE((is(U'b').is(ins    )) == false);
            REQUIRE((is(U'a').is(ins_eof)) == false);
        }
    }

    TEST_CASE( "testing is_not function overloads", "[is-not]" )
    {
        SECTION("char tests")
        {
            input_stream_dummy<char> ins('a');
            input_stream_dummy<char> ins_eof(std::char_traits<char>::eof());

            REQUIRE((is_not('a').is(ins    )) == false);
            REQUIRE((is_not('b').is(ins    )) == true );
            REQUIRE((is_not('a').is(ins_eof)) == true );
        }

        SECTION("wchar_t tests")
        {
            input_stream_dummy<wchar_t> ins(L'a');
            input_stream_dummy<wchar_t> ins_eof(std::char_traits<wchar_t>::eof());

            REQUIRE((is_not(L'a').is(ins    )) == false);
            REQUIRE((is_not(L'b').is(ins    )) == true );
            REQUIRE((is_not(L'a').is(ins_eof)) == true );
        }

        SECTION("char16_t tests")
        {
            input_stream_dummy<char16_t> ins(u'a');
            input_stream_dummy<char16_t> ins_eof(std::char_traits<char16_t>::eof());

            REQUIRE((is_not(u'a').is(ins    )) == false);
            REQUIRE((is_not(u'b').is(ins    )) == true );
            REQUIRE((is_not(u'a').is(ins_eof)) == true );
        }

        SECTION("char32_t tests")
        {
            input_stream_dummy<char32_t> ins(U'a');
            input_stream_dummy<char32_t> ins_eof(std::char_traits<char32_t>::eof());

            REQUIRE((is_not(U'a').is(ins    )) == false);
            REQUIRE((is_not(U'b').is(ins    )) == true );
            REQUIRE((is_not(U'a').is(ins_eof)) == true );
        }
    }


    TEST_CASE( "testing is_one_of function overloads", "[is-one-of]" )
    {
        SECTION("char tests")
        {
            input_stream_dummy<char> ins('a');
            input_stream_dummy<char> ins_eof(std::char_traits<char>::eof());

            REQUIRE((is_one_of('a'     ).is(ins    )) == true );
            REQUIRE((is_one_of('b'     ).is(ins    )) == false);
            REQUIRE((is_one_of('a', 'b').is(ins    )) == true );
            REQUIRE((is_one_of('b', 'a').is(ins    )) == true );
            REQUIRE((is_one_of('b', 'c').is(ins    )) == false);
            REQUIRE((is_one_of('a'     ).is(ins_eof)) == false);
            REQUIRE((is_one_of('a', 'b').is(ins_eof)) == false);


        }

        SECTION("wchar_t tests")
        {
            input_stream_dummy<wchar_t> ins(L'a');
            input_stream_dummy<wchar_t> ins_eof(std::char_traits<wchar_t>::eof());

            REQUIRE((is_one_of(L'a'      ).is(ins    )) == true );
            REQUIRE((is_one_of(L'b'      ).is(ins    )) == false);
            REQUIRE((is_one_of(L'a', L'b').is(ins    )) == true );
            REQUIRE((is_one_of(L'b', L'a').is(ins    )) == true );
            REQUIRE((is_one_of(L'b', L'c').is(ins    )) == false);
            REQUIRE((is_one_of(L'a'      ).is(ins_eof)) == false);
            REQUIRE((is_one_of(L'a', L'b').is(ins_eof)) == false);
        }

        SECTION("char16_t tests")
        {
            input_stream_dummy<char16_t> ins(u'a');
            input_stream_dummy<char16_t> ins_eof(std::char_traits<char16_t>::eof());

            REQUIRE((is_one_of(u'a'      ).is(ins    )) == true );
            REQUIRE((is_one_of(u'b'      ).is(ins    )) == false);
            REQUIRE((is_one_of(u'a', u'b').is(ins    )) == true );
            REQUIRE((is_one_of(u'b', u'a').is(ins    )) == true );
            REQUIRE((is_one_of(u'b', u'c').is(ins    )) == false);
            REQUIRE((is_one_of(u'a'      ).is(ins_eof)) == false);
            REQUIRE((is_one_of(u'a', u'b').is(ins_eof)) == false);
        }

        SECTION("char32_t tests")
        {
            input_stream_dummy<char32_t> ins(U'a');
            input_stream_dummy<char32_t> ins_eof(std::char_traits<char32_t>::eof());

            REQUIRE((is_one_of(U'a'      ).is(ins    )) == true );
            REQUIRE((is_one_of(U'b'      ).is(ins    )) == false);
            REQUIRE((is_one_of(U'a', U'b').is(ins    )) == true );
            REQUIRE((is_one_of(U'b', U'a').is(ins    )) == true );
            REQUIRE((is_one_of(U'b', U'c').is(ins    )) == false);
            REQUIRE((is_one_of(U'a'      ).is(ins_eof)) == false);
            REQUIRE((is_one_of(U'a', U'b').is(ins_eof)) == false);
        }
    }

    TEST_CASE( "testing is_none_of function overloads", "[is-none-of]" )
    {
        SECTION("char tests")
        {
            input_stream_dummy<char> ins('a');
            input_stream_dummy<char> ins_eof(std::char_traits<char>::eof());

            REQUIRE((is_none_of('a'     ).is(ins    ))  == false);
            REQUIRE((is_none_of('b'     ).is(ins    ))  == true );
            REQUIRE((is_none_of('a', 'b').is(ins    ))  == false);
            REQUIRE((is_none_of('b', 'a').is(ins    ))  == false);
            REQUIRE((is_none_of('b', 'c').is(ins    ))  == true );
            REQUIRE((is_none_of('a'     ).is(ins_eof))  == true );
            REQUIRE((is_none_of('a', 'b').is(ins_eof))  == true );
        }

        SECTION("wchar_t tests")
        {
            input_stream_dummy<wchar_t> ins(L'a');
            input_stream_dummy<wchar_t> ins_eof(std::char_traits<wchar_t>::eof());

            REQUIRE((is_none_of(L'a'      ).is(ins    ))  == false);
            REQUIRE((is_none_of(L'b'      ).is(ins    ))  == true );
            REQUIRE((is_none_of(L'a', L'b').is(ins    ))  == false);
            REQUIRE((is_none_of(L'b', L'a').is(ins    ))  == false);
            REQUIRE((is_none_of(L'b', L'c').is(ins    ))  == true );
            REQUIRE((is_none_of(L'a'      ).is(ins_eof))  == true );
            REQUIRE((is_none_of(L'a', L'b').is(ins_eof))  == true );
        }

        SECTION("char16_t tests")
        {
            input_stream_dummy<char16_t> ins(u'a');
            input_stream_dummy<char16_t> ins_eof(std::char_traits<char16_t>::eof());

            REQUIRE((is_none_of(u'a'      ).is(ins    ))  == false);
            REQUIRE((is_none_of(u'b'      ).is(ins    ))  == true );
            REQUIRE((is_none_of(u'a', u'b').is(ins    ))  == false);
            REQUIRE((is_none_of(u'b', u'a').is(ins    ))  == false);
            REQUIRE((is_none_of(u'b', u'c').is(ins    ))  == true );
            REQUIRE((is_none_of(u'a'      ).is(ins_eof))  == true );
            REQUIRE((is_none_of(u'a', u'b').is(ins_eof))  == true );
        }

        SECTION("char32_t tests")
        {
            input_stream_dummy<char32_t> ins(U'a');
            input_stream_dummy<char32_t> ins_eof(std::char_traits<char32_t>::eof());

            REQUIRE((is_none_of(U'a'      ).is(ins    ))  == false);
            REQUIRE((is_none_of(U'b'      ).is(ins    ))  == true );
            REQUIRE((is_none_of(U'a', U'b').is(ins    ))  == false);
            REQUIRE((is_none_of(U'b', U'a').is(ins    ))  == false);
            REQUIRE((is_none_of(U'b', U'c').is(ins    ))  == true );
            REQUIRE((is_none_of(U'a'      ).is(ins_eof))  == true );
            REQUIRE((is_none_of(U'a', U'b').is(ins_eof))  == true );
        }
    }

    TEST_CASE("testing sequential example", "[sequential]")
    {
        SECTION("valid input")
        {
            static constexpr int expected_result[] = {
                -3, -3, -2, -1, 0, -1, 0, 1, 1, 2, 2, 2, 4, 5, 8
            };

            whirl::code_position pos{ 1, 1 };

            std::ifstream ifs("sequential.inp");

            REQUIRE(ifs.is_open());

            const auto result = sequential::read_data_entries(ifs, pos);

            REQUIRE(std::equal(std::begin(result), std::end(result), std::begin(expected_result)));
        }

        SECTION("invalid input")
        {
            whirl::code_position pos{ 1, 1 };

            std::ifstream ifs("sequential_invalid.inp");

            REQUIRE_THROWS(sequential::read_data_entries(ifs, pos));
        }

        SECTION("empty input")
        {
            whirl::code_position pos{ 1, 1 };

            std::istringstream iss;

            const auto result = sequential::read_data_entries(iss, pos);

            REQUIRE(result.empty());
        }
    }

}