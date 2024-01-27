# Sidal
This application uses `sida.medu.ir` api to generate the final result of school grade information

# Build
1. Install [rustup](https://www.rust-lang.org/tools/install)
2. Open CMD and run the following command:
```bat
    rustup target add x86_64-pc-windows-msvc
    rustup target add i686-pc-windows-msvc
```
2. Install [node-js](https://nodejs.org/en)
3. Clone the repository
4. Open CMD on your directory
5. Use the following command to open repository directory:
```bat
    cd "[your repository directory]"
```
6. Run the following command to build 64bit version :
```bat
    npm run build_x64
```
7. Run the following command to build 32bit version :
```bat
    npm run build_x86
```