[@bs.deriving abstract]
type initialiseYTArgs = {
  height: int,
  width: int,
  videoId: string,
};

let init = () => {
  let player = Webapi.Dom.document |> Webapi.Dom.Document.getElementById("player");
  switch (player) {
  | None =>
    let body = Webapi.Dom.document |> Webapi.Dom.Document.querySelector("body");
    let script = Webapi.Dom.document |> Webapi.Dom.Document.createElement("script");
    Webapi.Dom.Element.setAttribute("src", "https://www.youtube.com/iframe_api", script);
    switch (body) {
    | None => print_endline("Could not append script tag")
    | Some(body) => Webapi.Dom.Element.appendChild(script, body)
    };
  | Some(_) => print_endline("Player already initialised")
  };
};

type t;

type playerInfoType = {
  author: string,
  title: string,
  video_id: string,
  video_quality: string,
  video_quality_features: string,
};

[@bs.deriving abstract]
type youtubeApiType = {
  [@bs.as "A"]
  methodsLoaded: bool,
  [@bs.optional]
  getVideoData: playerInfoType,
};

[@bs.deriving abstract]
type loadCueVideo = {
  videoId: string,
  [@bs.optional]
  startSeconds: int,
  [@bs.optional]
  endSeconds: int,
  [@bs.optional]
  suggestedQuality: string,
};

[@bs.deriving abstract]
type loadCueVideoUrl = {
  mediaContentUrl: string,
  [@bs.optional]
  startSeconds: int,
  [@bs.optional]
  endSeconds: int,
  [@bs.optional]
  suggestedQuality: string,
};

/*Initial creatio*/
[@bs.new] external createYoutubePlayer : (string, initialiseYTArgs) => youtubeApiType = "YT.Player";

/*Loading Videos*/
[@bs.send] external loadVideoById : (youtubeApiType, loadCueVideo) => unit = "";

[@bs.send] external cueVideoById : (youtubeApiType, loadCueVideo) => unit = "";

[@bs.send] external loadVideoByUrl : (youtubeApiType, loadCueVideoUrl) => unit = "";

[@bs.send] external cueVideoByUrl : (youtubeApiType, loadCueVideoUrl) => unit = "";

/*Player Controls*/
[@bs.send] external playVideo : youtubeApiType => unit = "";

[@bs.send] external pauseVideo : youtubeApiType => unit = "";

[@bs.send] external stopVideo : youtubeApiType => unit = "";

[@bs.send] external seekTo : (youtubeApiType, int, bool) => unit = "";

[@bs.send] external nextVideo : youtubeApiType => unit = "";

[@bs.send] external previousVideo : youtubeApiType => unit = "";

[@bs.send] external playVideoAt : (youtubeApiType, int) => unit = "";

[@bs.send] external mute : youtubeApiType => unit = "";

[@bs.send] external unMute : youtubeApiType => unit = "";

[@bs.send] external isMuted : youtubeApiType => bool = "";

[@bs.send] external setVolume : (youtubeApiType, int) => unit = "";

[@bs.send] external getVolume : youtubeApiType => int = "";

[@bs.send] external setSize : (youtubeApiType, ~height: int, ~width: int) => unit = "";

[@bs.send] external getPlaybackRate : youtubeApiType => int = "";

[@bs.send] external setPlaybackRate : (youtubeApiType, float) => unit = "";

[@bs.send] external getAvailablePlaybackRates : youtubeApiType => array(int) = "";

[@bs.send] external setLoop : (youtubeApiType, bool) => unit = "";

[@bs.send] external setShuffle : (youtubeApiType, bool) => unit = "";

/*TODO: Figure out how to limit these*/
type sphericalProperties = {
  yaw: int, /*0 to 360*/
  pitch: int, /*-90 to 90*/
  roll: int, /*-180 to 180*/
  fov: int /*30 to 120*/
};

[@bs.send] external getSphericalProperties : youtubeApiType => sphericalProperties = "";

[@bs.send] external setSphericalProperties : (youtubeApiType, sphericalProperties) => unit = "";

/*Player Status*/ [@bs.send] external getVideoLoadedFraction : youtubeApiType => float = "";

[@bs.send] external getPlayerState : youtubeApiType => int = "";

[@bs.send] external getCurrentTime : youtubeApiType => int = "";

[@bs.send] external getVideoStartBytes : youtubeApiType => int = "";

[@bs.send] external getVideoBytesLoaded : youtubeApiType => int = "";

[@bs.send] external getVideoBytesTotal : youtubeApiType => int = "";

[@bs.send] external getPlaybackQuality : youtubeApiType => string = "";

[@bs.send] external setPlaybackQuality : (youtubeApiType, ~suggestedQuality: string) => unit = "";

[@bs.send] external getDuration : youtubeApiType => int = "";

[@bs.send] external getVideoData : youtubeApiType => playerInfoType = "";

[@bs.send] external getVideoUrl : youtubeApiType => string = "";

[@bs.send] external getVideoEmbedCode : youtubeApiType => string = "";

[@bs.send] external getPlaylistIndex : youtubeApiType => int = "";

/*[@bs.send] external addEventListener : (youtubeApiType, ~event: string, ~listener: string) => unit = "";*/
/*[@bs.send] external removeEventListener : (youtubeApiType, ~event: string, ~listener: string) => unit = "";*/
/*TODO: Type the iframe */
[@bs.send] external getIframe : youtubeApiType => unit = "";

[@bs.send] external destroy : youtubeApiType => unit = "";

[@bs.send] external getAvailableQualityLevels : youtubeApiType => array(string) = "";

[@bs.send] external getPlaylist : youtubeApiType => array(string) = "";

/* Methods check to see whether they are initialised by the youtube API to prevent runtime error */
let playVideo = obj => obj |. methodsLoaded ? playVideo(obj) : ();

let pauseVideo = obj => obj |. methodsLoaded ? pauseVideo(obj) : ();

let stopVideo = obj => obj |. methodsLoaded ? stopVideo(obj) : ();

let seekTo = (obj, time, allowSeekAhead) => obj |. methodsLoaded ? seekTo(obj, time, allowSeekAhead) : ();

let nextVideo = obj => obj |. methodsLoaded ? nextVideo(obj) : ();

let previousVideo = obj => obj |. methodsLoaded ? previousVideo(obj) : ();

let playVideoAt = (obj, time) => obj |. methodsLoaded ? playVideoAt(obj, time) : ();

let mute = obj => obj |. methodsLoaded ? mute(obj) : ();

let unMute = obj => obj |. methodsLoaded ? unMute(obj) : ();

let isMuted = obj => obj |. methodsLoaded ? isMuted(obj) : false;

let setVolume = (obj, vol) => obj |. methodsLoaded ? setVolume(obj, vol) : ();

let getVolume = obj => obj |. methodsLoaded ? getVolume(obj) : 0;

let setSize = (obj, ~height, ~width) => obj |. methodsLoaded ? setSize(obj, ~height, ~width) : ();

let getPlaybackRate = obj => obj |. methodsLoaded ? getPlaybackRate(obj) : 0;

let setPlaybackRate = (obj, rate) => obj |. methodsLoaded ? setPlaybackRate(obj, rate) : ();

let getAvailablePlaybackRates = obj => obj |. methodsLoaded ? getAvailablePlaybackRates(obj) : [|0|];

let setLoop = (obj, loop) => obj |. methodsLoaded ? setLoop(obj, loop) : ();

let setShuffle = (obj, shuffle) => obj |. methodsLoaded ? setShuffle(obj, shuffle) : ();

let getSphericalProperties = obj =>
  obj |. methodsLoaded ?
    getSphericalProperties(obj) :
    {
      yaw: 0, /*0 to 360*/
      pitch: 0, /*-90 to 90*/
      roll: 0, /*-180 to 180*/
      fov: 30,
    };

let setSphericalProperties = (obj, sphericalProperties) =>
  obj |. methodsLoaded ? setSphericalProperties(obj, sphericalProperties) : ();

let getVideoLoadedFraction = obj => obj |. methodsLoaded ? getVideoLoadedFraction(obj) : 0.00;

let getPlayerState = obj => obj |. methodsLoaded ? getPlayerState(obj) : 0;

let getCurrentTime = obj => obj |. methodsLoaded ? getCurrentTime(obj) : 0;

let getVideoStartBytes = obj => obj |. methodsLoaded ? getVideoStartBytes(obj) : 0;

let getVideoBytesLoaded = obj => obj |. methodsLoaded ? getVideoBytesLoaded(obj) : 0;

let getVideoBytesTotal = obj => obj |. methodsLoaded ? getVideoBytesTotal(obj) : 0;

let getPlaybackQuality = obj => obj |. methodsLoaded ? getPlaybackQuality(obj) : "method not loaded yet";

let setPlaybackQuality = (obj, ~suggestedQuality) =>
  obj |. methodsLoaded ? setPlaybackQuality(obj, ~suggestedQuality) : ();

let getDuration = obj => obj |. methodsLoaded ? getDuration(obj) : 0;

let getVideoData = obj =>
  obj |. methodsLoaded ?
    getVideoData(obj) :
    {
      author: "author_not_found",
      title: "title_not_found",
      video_id: "video_id_not_found",
      video_quality: "video_quality_not_found",
      video_quality_features: "video_quality_features_not_found",
    };

let getVideoUrl = obj => obj |. methodsLoaded ? getVideoUrl(obj) : "method not loaded yet";

let getVideoEmbedCode = obj => obj |. methodsLoaded ? getVideoEmbedCode(obj) : "method not loaded yet";

let getPlaylistIndex = obj => obj |. methodsLoaded ? getPlaylistIndex(obj) : 0;

/*let addEventListener = obj => obj |. methodsLoaded  ? addEventListener(obj) : ();*/
/*let removeEventListener = obj => obj |. methodsLoaded  ? removeEventListener(obj) : ();*/
let getIframe = obj => obj |. methodsLoaded ? getIframe(obj) : ();

let destroy = obj => obj |. methodsLoaded ? destroy(obj) : ();

let getAvailableQualityLevels = obj =>
  obj |. methodsLoaded ? getAvailableQualityLevels(obj) : [|"method not loaded yet"|];

let getPlaylist = obj => obj |. methodsLoaded ? getPlaylist(obj) : [|"method not loaded yet"|];

/*TODO: Youtube iframe events*/
[@bs.deriving abstract]
type state = {
  mutable youtubeApi: youtubeApiType,
  mutable loaded: bool,
};

let youtubeState = state(~loaded=false, ~youtubeApi=youtubeApiType(~methodsLoaded=false, ()));

let createPlayer = (~height=390, ~width=640, ~videoId, ()) : unit => {
  let player = createYoutubePlayer("player", initialiseYTArgs(~height, ~width, ~videoId));
  youtubeState |. youtubeApiSet(player);
  ();
};

/*Util Functions*/
let getState = () => youtubeState;

let getPlayer = () => youtubeApi(youtubeState);

let isLoaded = () => loaded(youtubeState);

let setApiLoaded = () => youtubeState |. loadedSet(true);

[%bs.raw {|window.onYouTubeIframeAPIReady = setApiLoaded  |}];
