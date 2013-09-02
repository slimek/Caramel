// Caramel C++ Library - Program Facility - Program Options Header

#ifndef __CARAMEL_PROGRAM_PROGRAM_OPTIONS_H
#define __CARAMEL_PROGRAM_PROGRAM_OPTIONS_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/String/StringConvertible.h>


namespace Caramel
{

//
// USAGE:
//
//   This is a lightweight program options facility, which let you to declare
//   options in separate CPP files.
//
//   Based on Boost.ProgramOptions library.
//   You may see its document for the options argument rules.
//
//   When the program enters the main entry, call ProgramOptions::ParseCommandLine()
//   to generate all declared option values.
// 
//   The following class would also automatically parse the command line:
//
//     ConsoleApplication
//

///////////////////////////////////////////////////////////////////////////////
//
// Program Options
// - Management to the whole facility.
//

class ProgramOptions
{
public:

    //
    // Throws if parse failed.
    // - For example, if an option required an integer but the input command
    //   line has no argument, or it can not be converted to an integer.
    //
    static void ParseCommandLine();

};


///////////////////////////////////////////////////////////////////////////////
//
// Program Option Value
// - Base class of other concrete value types.
//

class ProgramOptionValue
{
public:

    virtual ~ProgramOptionValue() {}

    Bool Exists() const;

    std::string GetLongName() const { return m_longName; }


protected:
    
    //
    // If there is no ',' in name, it is a long name.
    // Otherwise the part before ',' is long name, and after it is short name.
    //
    explicit ProgramOptionValue( const std::string& name );

    std::string m_longName;
};


///////////////////////////////////////////////////////////////////////////////
//
// Program Option Bool
//
// EXAMPLE:
//   static const ProgramOptionBool s_quiet( "quiet,q" );
//
//   The default value of the boolean is always false, that means the option
//   doesn't exist in the command line arguments.
//

class ProgramOptionBool : public ProgramOptionValue
{
public:

    explicit ProgramOptionBool( const std::string& name );

    
    /// Conversions ///

    Bool ToBool() const { return this->Exists(); }

    operator Bool() const { return this->Exists(); }
};


///////////////////////////////////////////////////////////////////////////////
//
// Program Option String
//
// EXAMPLE:
//   static const ProgramOptionString s_name( "name,n" );
//   static const ProgramOptionString s_code( "code,c", "1234" );
//

class ProgramOptionString : public ProgramOptionValue
                          , public StringConvertible< ProgramOptionString >
{
public:

    explicit ProgramOptionString( const std::string& name );
    ProgramOptionString( const std::string& name, const std::string& defaultValue );


    /// Conversions ///

    std::string ToString() const;

    operator std::string() const { return this->ToString(); }
};


///////////////////////////////////////////////////////////////////////////////
//
// Positional Program Option Values
// - A program can create positional options only one time.
//   You may register at most 3 option values.
//

class PositionalProgramOptionValues
{
public:
    explicit PositionalProgramOptionValues(
        const ProgramOptionValue& value1
    );

    PositionalProgramOptionValues(
        const ProgramOptionValue& value1,
        const ProgramOptionValue& value2
    );

    PositionalProgramOptionValues(
        const ProgramOptionValue& value1,
        const ProgramOptionValue& value2,
        const ProgramOptionValue& value3
    );
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_PROGRAM_PROGRAM_OPTIONS_H
