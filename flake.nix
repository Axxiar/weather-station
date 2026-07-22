{
  description = "Dev shell with Arduino IDE";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-parts.url = "github:hercules-ci/flake-parts";
  };

  outputs = inputs@{ flake-parts, nixpkgs, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = [
        "x86_64-linux"
        "aarch64-linux"
        "x86_64-darwin"
        "aarch64-darwin"
      ];

      perSystem = { system, pkgs, ... }: {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            arduino-ide
          ];

          shellHook = ''
            echo "Arduino IDE installed"
          '';
        };
      };
    };
}
