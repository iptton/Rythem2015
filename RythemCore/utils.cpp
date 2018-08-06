#include <Security/AuthorizationTags.h>
#include <Security/Authorization.h>
#include <vector>
#include <string>
#include <unistd.h>

#include <sys/param.h>
#include <mach-o/dyld.h>




bool executeCmdWithRoot(const std::string &program, const std::vector<std::string> &arguments){
    AuthorizationRef ref;
    if (AuthorizationCreate(NULL, kAuthorizationEmptyEnvironment, kAuthorizationFlagDefaults, &ref) != errAuthorizationSuccess) {
        return false;
    }

    AuthorizationItem item = {
        kAuthorizationRightExecute, 0, 0, 0
    };
    AuthorizationRights rights = { 1, &item };
    const AuthorizationFlags flags = kAuthorizationFlagDefaults
                                   | kAuthorizationFlagInteractionAllowed
                                   | kAuthorizationFlagPreAuthorize
                                   | kAuthorizationFlagExtendRights;

    if (AuthorizationCopyRights(ref, &rights, kAuthorizationEmptyEnvironment, flags, 0) != errAuthorizationSuccess) {
        AuthorizationFree(ref, kAuthorizationFlagDestroyRights);
        return false;
    }

    std::vector<char*> args;
    for (std::vector<std::string>::const_iterator it = arguments.begin(); it != arguments.end(); ++it) {
        args.push_back((char*)it->c_str());
    }
    args.push_back(0);

    OSStatus status = AuthorizationExecuteWithPrivileges(ref, program.c_str(), kAuthorizationFlagDefaults, &args[0], 0);

    AuthorizationFree(ref, kAuthorizationFlagDestroyRights);
    return status == errAuthorizationSuccess;
}

