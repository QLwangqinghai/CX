// swift-tools-version:5.4

import PackageDescription

let package = Package(
	name: "CX",
    products: [
        .library(name: "CX", type: .dynamic, targets: ["CX"]),
//        .executable(name: "CXTests", targets: ["CXTests"]),
    ],
    dependencies: [],
    targets: [
        .target(name: "CX", dependencies: [], path: "Sources/CX", exclude: [], sources: nil, publicHeadersPath: "include", cSettings: [.headerSearchPath("internal")], cxxSettings: nil, swiftSettings: nil, linkerSettings: nil),
//        .target(name: "CXTests", dependencies: ["CX"], path: "CXTests", exclude: [], sources: nil, cSettings: [], cxxSettings: nil, swiftSettings: nil, linkerSettings: nil),

    ],
    cLanguageStandard: .c11
)
