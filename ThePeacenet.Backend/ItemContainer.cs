﻿using Microsoft.Xna.Framework.Content;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ThePeacenet.Backend.AssetTypes;

namespace ThePeacenet.Backend
{
    /// <summary>
    /// Represents an object which loads and contains every single item in the game.
    /// </summary>
    public class ItemContainer
    {
        private AssetLoaderConfigData _config = null;
        private ContentManager _content = null;

        private List<Asset> _assets = new List<Asset>();
        
        public ItemContainer(ContentManager content)
        {
            _content = content ?? throw new ArgumentNullException(nameof(content));
            _config = _content.Load<AssetLoaderConfigData>("AssetLoaderConfig");
        }

        private async Task<List<T>> SearchContent<T>(string directory)
        {
            Console.WriteLine("Searching for content of type {0} in directory {1}", typeof(T).Name, directory);

            var list = new List<T>();

            foreach(var subdirectory in Directory.GetDirectories(directory))
            {
                string truePath = subdirectory.Replace(Path.DirectorySeparatorChar, '/').Remove(0, _content.RootDirectory.Length + 1);
                if (_config.DirectoryBlacklist.Contains(truePath)) continue;

                list.AddRange(await SearchContent<T>(subdirectory));
            }

            foreach(var file in Directory.GetFiles(directory))
            {
                string truePath = file.Replace(Path.DirectorySeparatorChar, '/').Remove(0, _content.RootDirectory.Length + 1);
                truePath = truePath.Remove(truePath.LastIndexOf('.'));

                try
                {
                    var data = _content.Load<T>(truePath);
                    Console.WriteLine(truePath);
                    list.Add(data);
                }
                catch { }
            }

            return list;
        }

        private async Task BuildAssets<T, TBuiltType>(List<T> data) where TBuiltType: Asset where T: AssetBuilder<TBuiltType>
        {
            Console.WriteLine("Building {0} Assets", typeof(TBuiltType).Name);

            foreach(var asset in data)
            {
                await Task.Run(() =>
                {
                    TBuiltType builtAsset = asset.Build(this);
                    this._assets.Add(builtAsset);
                });
            }
        }

        public async Task LoadAsync()
        {
            Console.WriteLine("Loading game assets...");

            await Task.Run(() =>
            {
                this._assets = new List<Asset>();
            });

            var assetRoot = _content.RootDirectory;

            var protocolData = await SearchContent<ProtocolData>(assetRoot);
            var protoImplData = await SearchContent<ProtocolImplementationData>(assetRoot);
            var exploitData = await SearchContent<ExploitData>(assetRoot);

            Console.WriteLine("Building assets...");

            await BuildAssets<ProtocolData, Protocol>(protocolData);
            await BuildAssets<ProtocolImplementationData, ProtocolImplementation>(protoImplData);
            await BuildAssets<ExploitData, Exploit>(exploitData);
        }

        public T GetItem<T>(string id) where T: Asset
        {
            return _assets
                .Where(x => x is T)
                .FirstOrDefault(x => x.Id == id)
                as T;
        }
    }
}