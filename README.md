# bs-youtube

bs-youtube is a statically typed interface to the [Youtube iFrame API](https://developers.google.com/youtube/iframe_api_reference)

## Installation

```sh
npm install --save bs-youtube
```

In your `bsconfig.json`, include `"bs-youtube"` in the `bs-dependencies`.

## Usage

See `example/example.re` for sample usage.

```reason

/*Have to init the API before doing anything else */
Youtube.init();

let player = Youtube.getPlayer();

/*To play the currently loaded video */
Youtube.playVideo(player)
```

## Example

```sh
npm run build && npm run webpack
cd example
python -m SimpleHTTPServer 8080
Go to [Localhost](http://localhost:8080)
(Or whatever http server you want to use)
```

## Development

```sh
npm run start
```

## Documentation
See `example/example.re` for sample usage and the [Youtube API Docs](https://developers.google.com/youtube/iframe_api_reference) for documentation of what the methods do.

## TODO:
- Documentation
- Event listeners 
- Events
- Probably refactor and make better. 
- Test 360 Videos 
