#define CI_BUILD
#include "../ios_compat.h"
#pragma once

#include <string>
#include <vector>
#include <functional>
#include <memory>

namespace iOS {
namespace AdvancedBypass {

    /**
     * @class LoadstringSupport
     * @brief Provides robust loadstring implementation for all execution methods
     * 
     * This class implements loadstring functionality that works consistently across
     * all execution methods (WebKit, Method Swizzling, etc.) with advanced anti-detection
     * features and proper error handling.
     */
    class LoadstringSupport {
    public:
        // Loadstring result structure
        struct LoadResult {
            bool m_success;              // Loadstring operation succeeded
            std::string m_error;         // Error message if failed
            std::string m_bytecode;      // Generated bytecode (if applicable)
            std::string m_functionId;    // Function identifier for later execution
            
            LoadResult()
                : m_success(false) {}
                
            LoadResult(bool success, const std::string& error = "", 
                      const std::string& bytecode = "", const std::string& functionId = "")
                : m_success(success), m_error(error), 
                  m_bytecode(bytecode), m_functionId(functionId) {}
        };
        
        // Loadstring mode enumeration
        enum class Mode {
            Direct,         // Direct execution within current context
            StringEncoding, // String encoding for obfuscation
            BytecodeCompile, // Compile to bytecode for execution
            ProtectedCall   // Use pcall for protected execution
        };
        
    private:
        // Member variables with consistent m_ prefix
        Mode m_mode;                       // Current loadstring mode
        std::vector<std::string> m_funcs;  // Stored function IDs
        std::unordered_map<std::string, std::string> m_bytecodeCache; // Bytecode cache
        
        // Private methods
        std::string GenerateDirectLoadstring(const std::string& code, const std::string& chunkName = "");
        std::string GenerateEncodedLoadstring(const std::string& code, const std::string& chunkName = "");
        std::string GenerateBytecodeLoadstring(const std::string& code, const std::string& chunkName = "");
        std::string GenerateProtectedLoadstring(const std::string& code, const std::string& chunkName = "");
        std::string ObfuscateString(const std::string& str);
        std::string GenerateFunctionId();
        
    public:
        /**
         * @brief Constructor
         * @param mode Loadstring mode to use
         */
        LoadstringSupport(Mode mode = Mode::ProtectedCall);
        
        /**
         * @brief Destructor
         */
        ~LoadstringSupport();
        
        /**
         * @brief Generate loadstring code for a script
         * @param code Script code to load
         * @param chunkName Optional chunk name for error reporting
         * @return LoadResult containing success status and function ID
         */
        LoadResult GenerateLoadstring(const std::string& code, const std::string& chunkName = "");
        
        /**
         * @brief Generate code to execute a previously loaded function
         * @param functionId Function ID from a previous GenerateLoadstring call
         * @return String containing code to execute the function
         */
        std::string GenerateExecuteCode(const std::string& functionId);
        
        /**
         * @brief Generate complete loadstring and execute code
         * @param code Script code to load and execute
         * @param chunkName Optional chunk name for error reporting
         * @return String containing code to load and execute the script
         */
        std::string GenerateLoadAndExecute(const std::string& code, const std::string& chunkName = "");
        
        /**
         * @brief Set the loadstring mode
         * @param mode New loadstring mode
         */
        void SetMode(Mode mode);
        
        /**
         * @brief Get the current loadstring mode
         * @return Current loadstring mode
         */
        Mode GetMode() const;
        
        /**
         * @brief Clear stored function IDs and bytecode cache
         */
        void Clear();
        
        /**
         * @brief Get code for a loadstring implementation
         * @return Lua code for full loadstring implementation
         */
        static std::string GetLoadstringImplementation();
        
        /**
         * @brief Convert mode enum to string
         * @param mode Mode to convert
         * @return String representation of mode
         */
        static std::string ModeToString(Mode mode);
        
        /**
         * @brief Get a description of a mode
         * @param mode Mode to describe
         * @return Description of the mode
         */
        static std::string GetModeDescription(Mode mode);
    };

} // namespace AdvancedBypass
} // namespace iOS
