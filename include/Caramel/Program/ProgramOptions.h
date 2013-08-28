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
// Program Option
// - Base class of other concrete value types.
//

class ProgramOption
{
public:

    virtual ~ProgramOption() {}

    Bool Exists() const;


    //
    // Throws if parse failed.
    // - For example, if an option required an integer but the input command
    //   line has no argument, or it can not be converted to an integer.
    //
    static void ParseCommandLine();


protected:
    
    //
    // If there is no ',' in name, it is a long name.
    // Otherwise the part before ',' is long name, and after it is short name.
    //
    explicit ProgramOption( const std::string& name );

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

class ProgramOptionBool : public ProgramOption
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

class ProgramOptionString : public ProgramOption
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

} // namespace Caramel

#endif // __CARAMEL_PROGRAM_PROGRAM_OPTIONS_H
