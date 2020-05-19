﻿using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.IO;
using System.Net.Security;
using System.Text;
using System.Net;
using Newtonsoft.Json;
using NStack;
using Terminal.Gui;
using System.Runtime.InteropServices;

namespace C302SerializeJSON {
    class Program {
        const String CFolderMyApplication = "WorkJSON";
        const String CRemoteJSON = "http://resources.finance.ua/ru/public/currency-cash.json";
        const String CLocalJSON = "currency-cash.json";
        // поля для модели данных
        public static Reference Cities;
        public static Reference Regions;
        public static Reference Currencies;
        public static Reference OrgTypes;
        public static Organitations Orgs;
        // поля для элементов управления
        public static MenuBar MainMenu;
        // обработчики событий
        public static void miFileExit() {
            Application.Top.Running = false;
        }
        public static void miRefNew(String ATtile, Reference ARef) {
            Window LWndw = new Window(ATtile) {
                X = 0,
                Y = 1, // для меню оставим одну строчку
                Width = Dim.Fill(),
                Height = Dim.Fill()
            };
            LWndw.ColorScheme.Normal = Application.Driver.MakeAttribute(Color.Black, Color.Green);
            ListView LListViewRef = new ListView(
                new Rect() {
                    X = 0,
                    Y = 0,
                    Height = 25,
                    Width = 120
                },
                ARef);
            LWndw.Add(LListViewRef);
            Application.Top.Add(LWndw);
            Application.Run();
        }
        public static void miRefCities() {
            miRefNew("Города", Cities);
        }
        public static void miRefRegions() {
            miRefNew("Регионы", Regions);
        }
        public static void miRefCurrencies() {
            miRefNew("Валюты", Currencies);
        }
        public static void miRefOrgTypes() {
            miRefNew("Типы организаций", OrgTypes);
        }
        public static void miCources(OrgsItem AItem) {
            Window LWndw = new Window("Курсы валют у "+AItem.Name.PadRight(36));
            LWndw.X = 0;
            LWndw.Y = 1;
            LWndw.Width = Dim.Fill();
            LWndw.Height = Dim.Fill();
            LWndw.ColorScheme.Normal = Application.Driver.MakeAttribute(Color.White, Color.Red);
            ListView LListViewCource = new ListView(
                new Rect() {
                    X = 0,
                    Y = 0,
                    Height = 20,
                    Width = 50
                },
                AItem.Cources);
            LWndw.Add(LListViewCource);
            Application.Top.Add(LWndw);
            Application.Run();
        }
        public static void miRefOrgs() {
            void KeyDown(KeyEvent keyEvent, ListView AListView) {
                if(keyEvent.Key == Key.Enter) {
                    miCources(Orgs[AListView.SelectedItem]);
                }
            }
            Window LWndw = new Window("Организации");
            LWndw.X = 0;
            LWndw.Y = 1;
            LWndw.Width = Dim.Fill();
            LWndw.Height = Dim.Fill();
            /*
            {
                X = 0,
                Y = 1, // для меню оставим одну строчку
                Width = Dim.Fill(),
                Height = Dim.Fill()
            };
            */
            LWndw.ColorScheme.Normal = Application.Driver.MakeAttribute(Color.White, Color.Blue);
            ListView LListViewRef = new ListView(
                new Rect() {
                    X = 0,
                    Y = 0,
                    Height = 56,
                    Width = 156
                },
                Orgs);
            LListViewRef.OnKeyDown += (KeyEvent keyEvent) => KeyDown(keyEvent, LListViewRef);
            LWndw.Add(LListViewRef);
            Application.Top.Add(LWndw);
            Application.Run();
        }


        public static void DownloadFileText(String ARemoteURL, String ALocalPath) {
            WebRequest LWRQ = WebRequest.Create(ARemoteURL);
            LWRQ.Credentials = CredentialCache.DefaultCredentials;
            WebResponse LWR = LWRQ.GetResponse();
            Stream LStrm = LWR.GetResponseStream();
            StreamReader LReader = new StreamReader(LStrm);
            String LFileBody = LReader.ReadToEnd();
            LReader.Close();
            File.WriteAllText(ALocalPath, LFileBody);
        }
        public static String CheckFolders() {
            // I. установление путей в приложении
            // I.1 получаем путь к папке "Мои Документы"
            String LDefaultPath = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            // I.2 устанавливаем текущим путь "Мои Документы"
            Directory.SetCurrentDirectory(LDefaultPath);
            // I.3 проверяем наличие папки FolderMyApplication
            if(!Directory.Exists(CFolderMyApplication)) { // если нет
                Directory.CreateDirectory(CFolderMyApplication); // создаём эту папку
            }
            // I.4 получаем путь к папке "Мои Документы" \ FolderMyApplication
            LDefaultPath = Path.Combine(LDefaultPath, CFolderMyApplication);
            // устанавливаем этот путь текущим для приложения
            Directory.SetCurrentDirectory(LDefaultPath);
            return LDefaultPath;
        }
        public static void Main(string[] args) {
            // 1. проверка рабочего каталога приложения
            String LDefaultPath = CheckFolders();
            // 2. скачать файл из интернета
            if(!File.Exists(Path.Combine(LDefaultPath, CLocalJSON))) {
                DownloadFileText(CRemoteJSON, Path.Combine(LDefaultPath, CLocalJSON));
            }
            // 3. загрузить данные из файла
            String LJSON = File.ReadAllText(Path.Combine(LDefaultPath, CLocalJSON));
            var LCourceObject = JsonConvert.DeserializeObject<dynamic>(LJSON);
            // 4. создаём справочники
            Cities     = new Reference(LCourceObject.cities);
            Regions    = new Reference(LCourceObject.regions);
            Currencies = new Reference(LCourceObject.currencies);
            OrgTypes   = new Reference(LCourceObject.orgTypes);
            Orgs       = new Organitations(LCourceObject.organizations, OrgTypes, Regions, Cities, Currencies);


            Application.Init();
            // Создаём главное меню программы
            MenuItem LmiFileExit       = new MenuItem("Выход", "Выход из приложения", () => { miFileExit(); });
            MenuItem LmiRefsCities     = new MenuItem("Города", "", () => { miRefCities(); });
            MenuItem LmiRefsRegions    = new MenuItem("Регионы", "", () => { miRefRegions(); });
            MenuItem LmiRefsCurrencies = new MenuItem("Валюты", "", () => { miRefCurrencies(); });
            MenuItem LmiRefsOrgTypes   = new MenuItem("Типы организаций", "", () => { miRefOrgTypes(); });
            MenuItem LmiRefsOrgs       = new MenuItem("Организации", "", () => { miRefOrgs(); });

            MenuBarItem LbmiFile    = new MenuBarItem("Файл", new MenuItem[] { LmiFileExit } );
            MenuBarItem LbmiRefs    = new MenuBarItem("Справочники", new MenuItem[] { 
                LmiRefsCities, LmiRefsRegions, LmiRefsCurrencies, LmiRefsOrgTypes, LmiRefsOrgs
            });
            MainMenu = new MenuBar(new MenuBarItem[] {LbmiFile, LbmiRefs});

            // добавляем в приложение главное меню
            Application.Top.Add(MainMenu);


            Application.Run();
        }
    }
}