let pkgs = import <nixpkgs> { };
in with pkgs; rec {

# External Dependencies (personal)
  fil = (callPackage (builtins.fetchurl
    "https://raw.githubusercontent.com/FreeYourSoul/FiL/9a38ffe32a7cd709efe56bf7f05255259acb95a0/fil-recipee.nix") {
      rev = "903f138ab473c6249b58e1571191c71b61e912ab";
    });

}