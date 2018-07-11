/*Have to init the API before doing anything else */
Youtube.init();

module Example = {
  type state = {
    player: Youtube.state,
    timerId: ref(option(Js.Global.intervalId)),
  };

  type action =
    | LoadVideoById
    | CueVideoById
    | LoadVideoByUrl
    | CueVideoByUrl
    | PlayVideo
    | PauseVideo
    | StopVideo
    | SeekTo
    | NextVideo
    | PreviousVideo
    | PlayVideoAt
    | Mute
    | UnMute
    | IsMuted
    | SetVolume
    | GetVolume
    | SetSize
    | GetPlaybackRate
    | SetPlaybackRate
    | GetAvailablePlaybackRates
    | SetLoop
    | SetShuffle
    | GetVideoLoadedFraction
    | GetPlayerState
    | GetCurrentTime
    | GetVideoStartBytes
    | GetVideoBytesLoaded
    | GetVideoBytesTotal
    | GetPlaybackQuality
    | GetDuration
    | GetVideoData
    | GetVideoUrl
    | GetVideoEmbedCode
    | GetPlaylistIndex
    | AddEventListener
    | RemoveEventListener
    | GetIframe
    | Destroy
    | GetAvailableQualityLevels
    | GetPlaylist;

  let component = ReasonReact.reducerComponent("App");

  let clearTimer = state =>
    switch (state.timerId^) {
    | Some(id) => Js.Global.clearInterval(id)
    | None => ()
    };

  let make = _children => {
    ...component,
    initialState: () => {timerId: ref(None), player: Youtube.youtubeState},
    reducer: (action, state) => {
      let player = Youtube.getPlayer();
      switch (action) {
      | PlayVideo => Youtube.playVideo(player)
      | PauseVideo => Youtube.pauseVideo(player)
      | StopVideo => Youtube.stopVideo(player)
      | SeekTo => Youtube.seekTo(player, 10, true)
      | NextVideo => Youtube.nextVideo(player)
      | PreviousVideo => Youtube.previousVideo(player)
      | PlayVideoAt => Youtube.playVideoAt(player, 10)
      | Mute => Youtube.mute(player)
      | UnMute => Youtube.unMute(player)
      | IsMuted => Js.log(Youtube.isMuted(player))
      | SetVolume => Youtube.setVolume(player, 60)
      | GetVolume => Js.log(Youtube.getVolume(player))
      | SetSize => Youtube.setSize(player, ~height=100, ~width=100)
      | GetPlaybackRate => Js.log(Youtube.getPlaybackRate(player))
      | SetPlaybackRate => Youtube.setPlaybackRate(player, 1.25)
      | GetAvailablePlaybackRates => Js.log(Youtube.getAvailablePlaybackRates(player))
      | SetLoop => Youtube.setLoop(player, true)
      | SetShuffle => Youtube.setShuffle(player, true)
      | GetVideoLoadedFraction => Js.log(Youtube.getVideoLoadedFraction(player))
      | GetPlayerState => Js.log(Youtube.getPlayerState(player))
      | GetCurrentTime => Js.log(Youtube.getCurrentTime(player))
      | GetVideoStartBytes => Js.log(Youtube.getVideoStartBytes(player))
      | GetVideoBytesLoaded => Js.log(Youtube.getVideoBytesLoaded(player))
      | GetVideoBytesTotal => Js.log(Youtube.getVideoBytesTotal(player))
      | GetPlaybackQuality => Js.log(Youtube.getPlaybackQuality(player))
      | GetDuration => Js.log(Youtube.getDuration(player))
      | GetVideoData => Js.log(Youtube.getVideoData(player))
      | GetVideoUrl => Js.log(Youtube.getVideoUrl(player))
      | GetVideoEmbedCode => Js.log(Youtube.getVideoEmbedCode(player))
      | GetPlaylistIndex => Js.log(Youtube.getPlaylistIndex(player))
      | AddEventListener => Js.log("TODO: Youtube.addEventListener(player)")
      | RemoveEventListener => Js.log("TODO: Youtube.removeEventListener(player)")
      | GetIframe => Js.log(Youtube.getIframe(player))
      | Destroy => Youtube.destroy(player)
      | GetAvailableQualityLevels => Js.log(Youtube.getAvailableQualityLevels(player))
      | GetPlaylist => Js.log(Youtube.getPlaylist(player))
      | LoadVideoById =>
        Youtube.loadVideoById(
          player,
          Youtube.loadCueVideo(
            ~videoId="w1xPnuUWClU",
            ~startSeconds=80,
            ~endSeconds=60,
            ~suggestedQuality="large",
            (),
          ),
        )
      | CueVideoById =>
        Youtube.cueVideoById(
          player,
          Youtube.loadCueVideo(
            ~videoId="w1xPnuUWClU",
            ~startSeconds=80,
            ~endSeconds=60,
            ~suggestedQuality="large",
            (),
          ),
        )
      | LoadVideoByUrl =>
        Youtube.loadVideoByUrl(
          player,
          Youtube.loadCueVideoUrl(
            ~mediaContentUrl="https://www.youtube.com/watch?v=M7lc1UVf-VE",
            ~startSeconds=80,
            ~endSeconds=60,
            ~suggestedQuality="large",
            (),
          ),
        )
      | CueVideoByUrl =>
        Youtube.cueVideoByUrl(
          player,
          Youtube.loadCueVideoUrl(
            ~mediaContentUrl="https://www.youtube.com/watch?v=M7lc1UVf-VE",
            ~startSeconds=80,
            ~endSeconds=60,
            ~suggestedQuality="large",
            (),
          ),
        )
      };
      ReasonReact.Update(state);
    },
    didMount: self => {
      /*Check to see if the player has loaded from the Youtube API, and if so create the player*/
      let checker = () => {
        Js.log("check");
        let isLoaded = Youtube.isLoaded();
        isLoaded ?
          {
            clearTimer(self.state);
            self.state.timerId := None;
            Youtube.createPlayer(~videoId="w1xPnuUWClU", ());
          } :
          ();
      };
      self.state.timerId := Some(Js.Global.setInterval(checker, 1000));
    },
    willUnmount: self => clearTimer(self.state),
    render: self =>
      <div>
        <div className="App">
          <div className="App-header"> <h2> (ReasonReact.string("Reasonml Youtube Iframe Binding")) </h2> </div>
          <div> <h2> (ReasonReact.string("Youtube video:")) </h2> </div>
          <div id="player" />
          <div />
        </div>
        <button onClick=(_event => self.send(PlayVideo))> (ReasonReact.string("Play video")) </button>
        <button onClick=(_event => self.send(LoadVideoById))> (ReasonReact.string("Load video")) </button>
        <button onClick=(_event => self.send(CueVideoById))> (ReasonReact.string("Cue video")) </button>
        <button onClick=(_event => self.send(PauseVideo))> (ReasonReact.string("PauseVideo")) </button>
        <button onClick=(_event => self.send(StopVideo))> (ReasonReact.string("StopVideo")) </button>
        <button onClick=(_event => self.send(SeekTo))> (ReasonReact.string("SeekTo")) </button>
        <button onClick=(_event => self.send(NextVideo))> (ReasonReact.string("NextVideo")) </button>
        <button onClick=(_event => self.send(PreviousVideo))> (ReasonReact.string("PreviousVideo")) </button>
        <button onClick=(_event => self.send(PlayVideoAt))> (ReasonReact.string("PlayVideoAt")) </button>
        <button onClick=(_event => self.send(Mute))> (ReasonReact.string("Mute")) </button>
        <button onClick=(_event => self.send(UnMute))> (ReasonReact.string("Unmute")) </button>
        <button onClick=(_event => self.send(IsMuted))> (ReasonReact.string("IsMuted")) </button>
        <button onClick=(_event => self.send(SetVolume))> (ReasonReact.string("SetVolume")) </button>
        <button onClick=(_event => self.send(GetVolume))> (ReasonReact.string("GetVolume")) </button>
        <button onClick=(_event => self.send(SetSize))> (ReasonReact.string("SetSize")) </button>
        <button onClick=(_event => self.send(GetPlaybackRate))> (ReasonReact.string("GetPlaybackRate")) </button>
        <button onClick=(_event => self.send(SetPlaybackRate))> (ReasonReact.string("SetPlaybackRate")) </button>
        <button onClick=(_event => self.send(GetAvailablePlaybackRates))>
          (ReasonReact.string("GetAvailablePlaybackRates"))
        </button>
        <button onClick=(_event => self.send(SetLoop))> (ReasonReact.string("SetLoop")) </button>
        <button onClick=(_event => self.send(SetShuffle))> (ReasonReact.string("SetShuffle")) </button>
        <button onClick=(_event => self.send(GetVideoLoadedFraction))>
          (ReasonReact.string("GetVideoLoadedFraction"))
        </button>
        <button onClick=(_event => self.send(GetPlayerState))> (ReasonReact.string("GetPlayerState")) </button>
        <button onClick=(_event => self.send(GetCurrentTime))> (ReasonReact.string("GetCurrentTime")) </button>
        <button onClick=(_event => self.send(GetVideoStartBytes))>
          (ReasonReact.string("GetVideoStartBytes"))
        </button>
        <button onClick=(_event => self.send(GetVideoBytesLoaded))>
          (ReasonReact.string("GetVideoBytesLoaded"))
        </button>
        <button onClick=(_event => self.send(GetVideoBytesTotal))>
          (ReasonReact.string("GetVideoBytesTotal"))
        </button>
        <button onClick=(_event => self.send(GetPlaybackQuality))>
          (ReasonReact.string("GetPlaybackQuality"))
        </button>
        <button onClick=(_event => self.send(GetDuration))> (ReasonReact.string("GetDuration")) </button>
        <button onClick=(_event => self.send(GetVideoData))> (ReasonReact.string("GetVideoData")) </button>
        <button onClick=(_event => self.send(GetVideoUrl))> (ReasonReact.string("GetVideoUrl")) </button>
        <button onClick=(_event => self.send(GetVideoEmbedCode))> (ReasonReact.string("GetVideoEmbedCode")) </button>
        <button onClick=(_event => self.send(GetPlaylistIndex))> (ReasonReact.string("GetPlaylistIndex")) </button>
        <button onClick=(_event => self.send(AddEventListener))> (ReasonReact.string("AddEventListener")) </button>
        <button onClick=(_event => self.send(RemoveEventListener))>
          (ReasonReact.string("RemoveEventListener"))
        </button>
        <button onClick=(_event => self.send(GetIframe))> (ReasonReact.string("GetIframe")) </button>
        <button onClick=(_event => self.send(Destroy))> (ReasonReact.string("Destroy")) </button>
        <button onClick=(_event => self.send(GetAvailableQualityLevels))>
          (ReasonReact.string("GetAvailableQualityLevels"))
        </button>
        <button onClick=(_event => self.send(GetPlaylist))> (ReasonReact.string("GetPlaylist")) </button>
      </div>,
  };
};

ReactDOMRe.renderToElementWithId(<Example />, "app");
