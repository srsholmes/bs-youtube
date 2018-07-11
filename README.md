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

## Development

```sh
npm run start
```

## Documentation?
See `example/example.re` for sample usage and the [Youtube API Docs](https://developers.google.com/youtube/iframe_api_reference) for the methods you can access on the player.

## TODO:
- Documentation
- Event listeners 
- Events
- Probably refactor and make better. 
- Test 360 Videos 
