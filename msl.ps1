<#
.SYNOPSIS
    msl - Retrieve version, license, help, or library documentation.

.DESCRIPTION
    This script accepts a command and an optional path.
    --author          : Display the author name.
    --brief           : Display the a brief text about the project.
    --version         : Display the script version.
    --license         : Display the content of the license file.
    --help            : Display general usage help.
    --help <path>     : Display documentation for a specific library.

.PARAMETER Command
    The command: --author, --brief, --version, --license, or --help

.PARAMETER Path
    Optional library path for --help command

.EXAMPLE
    .\msl.ps1 --author
    .\msl.ps1 --brief
    .\msl.ps1 --version
    .\msl.ps1 --license
    .\msl.ps1 --help
    .\msl.ps1 --help cgen\micros.h
    .\msl.ps1 --help cgen/UnitTest.h
#>

param(
    [Parameter(Mandatory = $true, Position = 0)]
    [ValidateSet('--version', '--license', '--author', '--brief', '--help')]
    [string]$Command,
    
    [Parameter(Position = 1)]
    [string]$Path = $null
)

# ===================== Global Settings =====================
$script:Version = "beta 0.0.2"
$script:LicenseFile = Join-Path -Path $PSScriptRoot -ChildPath "documentation/lic.txt"
$script:HelpRoot = "help"
$script:briefFile = "documentation/brief.txt"

# ===================== Helper Functions =====================

function Show-Version {
    Write-Host "openMSL version $script:Version" -ForegroundColor Green
}

function Show-License {
    if (Test-Path $script:LicenseFile) {
        Write-Host "`n=== LICENSE ===`n" -ForegroundColor Yellow
        Get-Content $script:LicenseFile | ForEach-Object { Write-Host $_ }
    }
    else {
        Write-Error "License file not found: $script:LicenseFile"
        Write-Host "Please create a lic.txt file in the 'documentation' folder." -ForegroundColor Red
    }
}

function Show-Brief {
    if (Test-Path $script:briefFile) {
        Write-Host "`n=============== BRIEF ===============`n" -ForegroundColor Yellow
        Get-Content $script:briefFile | ForEach-Object { Write-Host $_ }
    }
    else {
        Write-Error "Brief file not found: $script:briefFile"
        Write-Host "Please create a brief.txt file in the 'documentation' folder." -ForegroundColor Red
    }
}

function Show-Help {
    $helpText = @"
===========================================
        mslCore - Information System
===========================================

Usage:
    .\msl.ps1 --brief
    .\msl.ps1 --author
    .\msl.ps1 --version
    .\msl.ps1 --license
    .\msl.ps1 --help
    .\msl.ps1 --help <path>

Options:
    --brief                 : Show a brief text about the project.
    --author                : Show the name of the author.
    --version               : Show script version.
    --license               : Show license content (from documentation/lic.txt).
    --help                  : Show this help message.
    --help <path>           : Show documentation for a specific library.
                              <path> is the library file path (e.g., lite/micros.h).
                              The script looks for documentation at:
                              documentation/text/<path_without_extension>.txt

Examples:
    .\msl.ps1 --help cgen/micros.hpp
    .\msl.ps1 --help cgen/UnitTest.h

Note:
    - The documentation root folder is 'documentation/text' relative to the script location.
    - Path separators can be '/' or '\' and are handled correctly.
    - Any file extension is removed and replaced with .txt.
"@
    Write-Host $helpText -ForegroundColor White
}

function Search-Help {
    param([string]$LibraryPath)

    # Normalize path separators to Windows backslash
    $normalizedPath = $LibraryPath -replace '/', '\'
    
    # Remove extension (everything after the last dot)
    $withoutExt = $normalizedPath -replace '\.[^.]*$', ''
    
    # Build the documentation file path inside help
    $docFileRelative = Join-Path -Path $script:HelpRoot -ChildPath "$withoutExt.txt"
    
    # Get absolute path (based on script location)
    $docFullPath = Join-Path -Path $PSScriptRoot -ChildPath $docFileRelative

    Write-Host "Looking for documentation of: $LibraryPath" -ForegroundColor Cyan
    Write-Host "Expected documentation file: $docFileRelative" -ForegroundColor DarkGray

    if (Test-Path $docFullPath) {
        Write-Host "`n=== Documentation for: $LibraryPath ===`n" -ForegroundColor Yellow
        Get-Content $docFullPath | ForEach-Object { Write-Host $_ }
    }
    else {
        Write-Error "Documentation file not found: $docFileRelative"
        Write-Host "Please ensure the file exists at: $docFullPath" -ForegroundColor Red
        exit 1
    }
}

# ===================== Main Logic =====================

if ($Command -eq "--author") {
    Write-Host "author: Ali Lafi (acting under the pseudonym `Ken Roth`)"
}
elseif ($Command -eq "--version") {
    Show-Version
}
elseif ($Command -eq "--license") {
    Show-License
}
elseif ($Command -eq "--brief") {
    Show-Brief
}
elseif ($Command -eq "--help") {
    if ($Path) {
        Search-Help -LibraryPath $Path
    }
    else {
        Show-Help
    }
}