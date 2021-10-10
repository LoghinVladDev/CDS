
//#include<io.h>
//#include<stdio.h>
//#include<winsock2.h>
//
//#include <CDS/Socket>
//
//#pragma comment(lib,"ws2_32.lib") //Winsock Library
//
//int main(int argc , char *argv[])
//{
//    WSADATA wsa;
//    SOCKET s , new_socket;
//    struct sockaddr_in server , client;
//    int c;
//    char *message;
//
//    printf("\nInitialising Winsock...");
//    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
//    {
//        printf("Failed. Error Code : %d",WSAGetLastError());
//        return 1;
//    }
//
//    printf("Initialised.\n");
//
//    //Create a socket
//    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
//    {
//        printf("Could not create socket : %d" , WSAGetLastError());
//    }
//
//    printf("Socket created.\n");
//
//    //Prepare the sockaddr_in structure
//    server.sin_family = AF_INET;
//    server.sin_addr.s_addr = INADDR_ANY;
//    server.sin_port = htons( 8888 );
//
//    //Bind
//    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
//    {
//        printf("Bind failed with error code : %d" , WSAGetLastError());
//        exit(EXIT_FAILURE);
//    }
//
//    puts("Bind done");
//
//    //Listen to incoming connections
//    listen(s , 3);
//
//    //Accept and incoming connection
//    puts("Waiting for incoming connections...");
//
//    c = sizeof(struct sockaddr_in);
//
//    while( (new_socket = accept(s , (struct sockaddr *)&client, &c)) != INVALID_SOCKET )
//    {
//        puts("Connection accepted");
//
//        //Reply to the client
//        message = "Hello Client , I have received your connection. But I have to go now, bye\n";
//        send(new_socket , message , 256 , 0);
//    }
//
//    if (new_socket == INVALID_SOCKET)
//    {
//        printf("accept failed with error code : %d" , WSAGetLastError());
//        return 1;
//    }
//
//    closesocket(s);
//    WSACleanup();
//
//    return 0;
//}

#include <CDS/Socket>
#include <CDS/Thread>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main () {
    ServerSocket serverSocket(34000, Socket::ProtocolVersion::FORCE_IPV6);

    Array < SharedPointer < Thread > > threads;

    while(true) {
        threads.pushBack (
            new Runnable ([socket = std::move(serverSocket.accept())] () mutable {

                socket.writeInt(socket.readInt() + 1);

                auto buffer = socket.readString();
                buffer.forEach([](char & character){++character;});
                socket.writeString(buffer);

                socket.close();
            })
        );

        threads.back()->start();
    }
}


//#include <iostream>
////#include <cstring>
////#include <exception>
//
////#include <CDS/Path>
////#include <unistd.h>
//
////#include <CDS/HashMap>
////#include <CDS/HashMap>
////#include <CDS/Sequence>
//#define CDS_DEBUG
//#include <CDS/Array>
//#include "ParallelSequence.hpp"
//#include <functional/Time.hpp>
//
//int main() {
//    ParallelSequence < LinkedList < int > > a ( {1, 2, 3} );
//
//    LinkedList < int > orig = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//    LinkedList < int > f;
//
//    decltype (a) :: ParallelFilterContainer b;
//
//    std::function < bool (int &) > filter1 = [] (int a) -> bool { return a % 2 == 1; };
//
//    b.pOriginalList = & orig;
//    b.pNewList = & f;
//
//    b.pPredicateList = new decltype(a)::StoredPredicateList;
//    b.pMapperList = new decltype(a)::StoredMapperList ;
//    b.pIndexedPredicateList = new decltype (a) :: StoredIndexedPredicateList ;
//    b.pIndexedMapperList = new decltype (a) :: StoredIndexedMapperList ;
//
//    auto p = Pair {
//        SharedPointer ( & filter1 ),
//        (Index) 1
//    };
//
//    b.chainCount = 2;
//    b.pPredicateList->pushBack( p );
//
//    decltype(a)::filterContainer( b );
//
//
//    std::cout << f << '\n';
////
////    UniquePointer p(new DoubleLinkedList {3, 4, 2});
////    p->sort([](auto a, auto b){return a < b;});
////    std::cout << p->toString() << '\n';
////    HashMap m = {Pair{4, 3}, Pair{3, 2}, Pair{3, 5}};
//
////    HashMap < String, float > m = {{"Vlad", 4.3f}, {"Andrei", 5.6f}};
////    m.view()
////        .filter([](auto & p){return p.getSecond() >= 4.5f;})
////        .map([](auto & p){return Pair{p.getFirst().upper(), p.getSecond()};})
////        .forEach([](auto & p){std::cout << p.getFirst() << '\n';});
//
////    LinkedList < int > l = {4, 3, 1};
////    l.view().filter([](auto & e){return e % 2 == 1;}).map([](auto & e){return e * 2;}).forEach([](auto & e){std::cout << e << ' ';});
//
////    String a = "Ana are mere";
////    std::cout << File::platformTypeFlagsToString(File::platformFileType("/")) << '\n';
////    std::cout << File::platformPermissionFlagsToStringList ( File::PlatformPermissionFlag::PPF_EXECUTE | File::PPF_READ ) << '\n';
////    std::cout << File::platformUserFlagsToString ( File::PUF_USER | File::PUF_OTHER ) << '\n';
////
////    std::cout << File::platformPermissionsGrouped ("/") << '\n';
////    try {
////        File::platformPermissionsGrouped("/home/loghin/work/dataStructures/main.cpp").forEach([](auto &p) {
////            std::cout << File::platformUserFlagToString(p.getFirst()) << " : "
////                      << File::platformPermissionFlagsToString(p.getSecond()) << '\n';
////        });
////
////        auto file = File::LinuxDirectory("/home/loghin");
////        file.directories().forEach([](auto * d){
////            std::cout << File::platformTypeFlagsToStringList (d->linuxFileType()) << " : " << d->name() << '\n';
////            d->entries().forEach([](auto * e){
////                std::cout << "\t" << File::platformTypeFlagsToStringList (e->linuxFileType()) << " : " << e->name() << ", size = " << e->linuxTotalSize() << '\n';
////            });
////        });
////
////
////    } catch (std::exception const & e) {
////        std::cout << e.what() << ", path hardcoded for testing purposes\n";
////    }
//
////    Path p;
////    for ( auto & e : p.walk() ) {
////        std::cout << e.root() << "\n\t" << e.files() << "\n\t" << e.directories() << "\n\n";
////    }
////
////    LinkedList < int > list = {1, 3, 7, 5};
////
////    int x = 3;
////    list.sort([](int a, int b){return a > b;});
////
////    std::cout << list.toString() << '\n';
////
////    HashMap < int, float > map = {{1, 3.4f}, {2, 6.7f}};
//}
////
////#include <windows.h>
////#include <stdio.h>
////
////void DisplayVolumePaths(
////        PWCHAR VolumeName
////)
////{
////    DWORD  CharCount = MAX_PATH + 1;
////    PWCHAR Names     = NULL;
////    PWCHAR NameIdx   = NULL;
////    BOOL   Success   = FALSE;
////
////    for (;;)
////    {
////        //
////        //  Allocate a buffer to hold the paths.
////        Names = (PWCHAR) new BYTE [CharCount * sizeof(WCHAR)];
////
////        if ( !Names )
////        {
////            //
////            //  If memory can't be allocated, return.
////            return;
////        }
////
////        //
////        //  Obtain all of the paths
////        //  for this volume.
////        Success = GetVolumePathNamesForVolumeNameW(
////                VolumeName, Names, CharCount, &CharCount
////        );
////
////        if ( Success )
////        {
////            break;
////        }
////
////        if ( GetLastError() != ERROR_MORE_DATA )
////        {
////            break;
////        }
////
////        //
////        //  Try again with the
////        //  new suggested size.
////        delete [] Names;
////        Names = NULL;
////    }
////
////    if ( Success )
////    {
////        //
////        //  Display the various paths.
////        for ( NameIdx = Names;
////              NameIdx[0] != L'\0';
////              NameIdx += wcslen(NameIdx) + 1 )
////        {
////            wprintf(L"  %s", NameIdx);
////        }
////        wprintf(L"\n");
////    }
////
////    if ( Names != NULL )
////    {
////        delete [] Names;
////        Names = NULL;
////    }
////
////    return;
////}
////
////int main()
////{
////    DWORD  CharCount            = 0;
////    WCHAR  DeviceName[MAX_PATH] = L"";
////    DWORD  Error                = ERROR_SUCCESS;
////    HANDLE FindHandle           = INVALID_HANDLE_VALUE;
////    BOOL   Found                = FALSE;
////    size_t Index                = 0;
////    BOOL   Success              = FALSE;
////    WCHAR  VolumeName[MAX_PATH] = L"";
////
////    //
////    //  Enumerate all volumes in the system.
////    FindHandle = FindFirstVolumeW(VolumeName, ARRAYSIZE(VolumeName));
////
////    if (FindHandle == INVALID_HANDLE_VALUE)
////    {
////        Error = GetLastError();
////        wprintf(L"FindFirstVolumeW failed with error code %d\n", Error);
////        return 1;
////    }
////
////    for (;;)
////    {
////        //
////        //  Skip the \\?\ prefix and remove the trailing backslash.
////        Index = wcslen(VolumeName) - 1;
////
////        if (VolumeName[0]     != L'\\' ||
////            VolumeName[1]     != L'\\' ||
////            VolumeName[2]     != L'?'  ||
////            VolumeName[3]     != L'\\' ||
////            VolumeName[Index] != L'\\')
////        {
////            Error = ERROR_BAD_PATHNAME;
////            wprintf(L"FindFirstVolumeW/FindNextVolumeW returned a bad path: %s\n", VolumeName);
////            break;
////        }
////
////        //
////        //  QueryDosDeviceW does not allow a trailing backslash,
////        //  so temporarily remove it.
////        VolumeName[Index] = L'\0';
////
////        CharCount = QueryDosDeviceW(&VolumeName[4], DeviceName, ARRAYSIZE(DeviceName));
////
////        VolumeName[Index] = L'\\';
////
////        if ( CharCount == 0 )
////        {
////            Error = GetLastError();
////            wprintf(L"QueryDosDeviceW failed with error code %d\n", Error);
////            break;
////        }
////
////        wprintf(L"\nFound a device:\n %s", DeviceName);
////        wprintf(L"\nVolume name: %s", VolumeName);
////        wprintf(L"\nPaths:");
////        DisplayVolumePaths(VolumeName);
////
////        //
////        //  Move on to the next volume.
////        Success = FindNextVolumeW(FindHandle, VolumeName, ARRAYSIZE(VolumeName));
////
////        if ( !Success )
////        {
////            Error = GetLastError();
////
////            if (Error != ERROR_NO_MORE_FILES)
////            {
////                wprintf(L"FindNextVolumeW failed with error code %d\n", Error);
////                break;
////            }
////
////            //
////            //  Finished iterating
////            //  through all the volumes.
////            Error = ERROR_SUCCESS;
////            break;
////        }
////    }
////
////    FindVolumeClose(FindHandle);
////    FindHandle = INVALID_HANDLE_VALUE;
////
////    return 0;
////}
#pragma clang diagnostic pop